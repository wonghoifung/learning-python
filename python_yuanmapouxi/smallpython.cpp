// reference: <<PythonÔ´ÂëÆÊÎö>>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <map>
#include <string>
#include <iostream>

// PyObject
#define PyObject_HEAD \
	int refCount; \
	struct tagPyTypeObject* type

#define PyObject_HEAD_INIT(typePtr) \
	0, typePtr

typedef struct tagPyObject {
	PyObject_HEAD;
} PyObject;

// PyTypeObject
typedef void (*PrintFun)(PyObject* object);
typedef PyObject* (*AddFun)(PyObject* left, PyObject* right);
typedef long (*HashFun)(PyObject* object);

typedef struct tagPyTypeObject {
	PyObject_HEAD;
	char* name;
	PrintFun print;
	AddFun add;
	HashFun hash;
} PyTypeObject;

PyTypeObject PyType_Type = {
	PyObject_HEAD_INIT(&PyType_Type),
	(char*)"type", 0, 0, 0
};

// PyIntObject
typedef struct tagPyIntObject {
	PyObject_HEAD;
	int value;
} PyIntObject;

PyObject* PyInt_Create(int value);

static void int_print(PyObject* object) {
	PyIntObject* intobject = (PyIntObject*)object;
	printf("%d\n", intobject->value);
}

static PyObject* int_add(PyObject* left, PyObject* right) {
	PyIntObject* leftint = (PyIntObject*)left;
	PyIntObject* rightint = (PyIntObject*)right;
	PyIntObject* result = (PyIntObject*)PyInt_Create(0);
	if (result == NULL) {
		printf("not enough memory\n");
		exit(1);
	}
	else {
		result->value = leftint->value + rightint->value;
	}
	return (PyObject*)result;
}

static long int_hash(PyObject* object) {
	return (long)((PyIntObject*)object)->value;
}

PyTypeObject PyInt_Type = {
	PyObject_HEAD_INIT(&PyType_Type),
	(char*)"int", int_print, int_add, int_hash
};

PyObject* PyInt_Create(int value) {
	PyIntObject* object = (PyIntObject*)new PyIntObject;
	object->refCount = 1;
	object->type = &PyInt_Type;
	object->value = value;
	return (PyObject*)object;
}

// PyStrObject
typedef struct tagPyStrObject {
	PyObject_HEAD;
	int length;
	long hashValue;
	char value[50];
} PyStrObject;

PyObject* PyStr_Create(const char* value);

static void str_print(PyObject* object) {
	PyStrObject* strobj = (PyStrObject*)object;
	printf("%s\n", strobj->value);
}

static PyObject* str_add(PyObject* left, PyObject* right) {
	PyStrObject* leftstr = (PyStrObject*)left;
	PyStrObject* rightstr = (PyStrObject*)right;
	PyStrObject* result = (PyStrObject*)PyStr_Create(NULL);
	if (result == NULL) {
		printf("not enough memory\n");
		exit(1);
	}
	else {
		strcpy(result->value, leftstr->value);
		strcat(result->value, rightstr->value);
	}
	return (PyObject*)result;
}

static long str_hash(PyObject* object) {
	PyStrObject* strobj = (PyStrObject*)object;
	register int len;
	register unsigned char* p;
	register long x;
	if (strobj->hashValue != -1) return strobj->hashValue;
	len = strobj->length;
	p = (unsigned char*)strobj->value;
	x = *p << 7;
	while (--len >= 0) x = (1000003 * x) ^ *p++;
	x ^= strobj->length;
	if (x == -1) x = -2;
	strobj->hashValue = x;
	return x;
}

PyTypeObject PyStr_Type = {
	PyObject_HEAD_INIT(&PyType_Type),
	(char*)"str", str_print, str_add, str_hash
};

PyObject* PyStr_Create(const char* value) {
	PyStrObject* object = (PyStrObject*)new PyStrObject;
	object->refCount = 1;
	object->type = &PyStr_Type;
	object->length = (value == NULL) ? 0 : strlen(value);
	object->hashValue = -1;
	memset(object->value, 0, 50);
	if (value) strcpy(object->value, value);
	return (PyObject*)object;
}

// PyDictObject
typedef struct tagPyDictObject {
	PyObject_HEAD;
	std::map<long, PyObject*> dict;
} PyDictObject;

static void dict_print(PyObject* object) {
	PyDictObject* dictobj = (PyDictObject*)object;
	printf("(\n");
	std::map<long, PyObject*>::iterator it = (dictobj->dict).begin();
	std::map<long, PyObject*>::iterator end = (dictobj->dict).end();
	for (; it != end; ++it) {
		printf("%ld : ", it->first);
		PyObject* value = it->second;
		(value->type)->print(value);
	}
	printf(")\n");
}

PyTypeObject PyDict_Type = {
	PyObject_HEAD_INIT(&PyType_Type),
	(char*)"dict", dict_print, 0, 0
};

PyObject* PyDict_Create() {
	PyDictObject* object = (PyDictObject*)new PyDictObject;
	object->refCount = 1;
	object->type = &PyDict_Type;
	return (PyObject*)object;
}

PyObject* PyDict_GetItem(PyObject* target, PyObject* key) {
	long keyhashvalue = (key->type)->hash(key);
	std::map<long, PyObject*>& dict = ((PyDictObject*)target)->dict;
	std::map<long, PyObject*>::iterator it = dict.find(keyhashvalue);
	if (it == dict.end()) return NULL;
	return it->second;
}

int PyDict_SetItem(PyObject* target, PyObject* key, PyObject* value) {
	long keyhashvalue = (key->type)->hash(key);
	PyDictObject* dictobj = (PyDictObject*)target;
	(dictobj->dict)[keyhashvalue] = value;
	return 0;
}

PyObject* local_env = PyDict_Create();

PyObject* GetObjectBySymbol(std::string symbol) {
	PyObject* key = PyStr_Create(symbol.c_str()); 
	PyObject* value = PyDict_GetItem(local_env, key);
	if (value == NULL) {
		printf("[error] : %s is not defined\n", symbol.c_str());
		delete key;
		return NULL;
	}
	delete key;
	return value;
}

void ExcutePrint(std::string symbol) {
	PyObject* object = GetObjectBySymbol(symbol);
	if (object != NULL) {
		PyTypeObject* type = object->type;
		type->print(object);
	}
}

bool IsSourceAllDigit(std::string& s) {
	for (int i = 0; i < s.size(); ++i) {
		if (!isdigit(s[i]))
			return false;
	}
	return true;
}

void ExcuteAssign(std::string& target, std::string& source) {
	std::string::size_type pos;
	if (IsSourceAllDigit(source)) {
		PyObject* intvalue = PyInt_Create(atoi(source.c_str()));
		PyObject* key = PyStr_Create(target.c_str());
		PyDict_SetItem(local_env, key, intvalue);
		delete key;
	}
	else if (source.find("\"") != std::string::npos) {
		PyObject* strvalue = PyStr_Create(source.substr(1, source.size() - 2).c_str());
		PyObject* key = PyStr_Create(target.c_str());
		PyDict_SetItem(local_env, key, strvalue);
		delete key;
	}
	else if ((pos = source.find("+")) != std::string::npos) {
		PyObject* resultvalue = NULL;
		PyObject* leftobj = GetObjectBySymbol(source.substr(0, pos));
		PyObject* rightobj = GetObjectBySymbol(source.substr(pos + 1));
		if (leftobj && rightobj && leftobj->type == rightobj->type) {
			resultvalue = (leftobj->type)->add(leftobj, rightobj);
			PyObject* key = PyStr_Create(target.c_str());
			PyDict_SetItem(local_env, key, resultvalue);
			delete key;
		}
	}
	(local_env->type)->print(local_env);
}

void ExcuteCommand(std::string& command) {
	std::string::size_type pos = 0;
	if ((pos = command.find("print ")) != std::string::npos) {
		ExcutePrint(command.substr(6));
	}
	else if ((pos = command.find(" = ")) != std::string::npos) {
		std::string target = command.substr(0, pos);
		std::string source = command.substr(pos + 3);
		ExcuteAssign(target, source);
	}
}

int main() {
	const char* prompt = ">>> ";
	std::string command;

	printf("%s", prompt);
	while (std::getline(std::cin, command)) {
		if (command.size() == 0) {
			printf("%s", prompt);
			continue;
		}
		else if (command == "exit") {
			return 0;
		}
		else {
			ExcuteCommand(command);
			printf("%s", prompt);
		}
	}
}
