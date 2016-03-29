#-*-coding:utf8-*-

import MySQLdb

class DisplayAttribute(object):
    def __str__(self):
        string = ''
        for key in self.__dict__:
            string += "%s: %s, " % (str(key), str(self.__dict__[key]))
        return string

class BaseException(Exception, DisplayAttribute):
    def __init__(self, err_code=0, err_desc=''):
        self.err_code = err_code
        self.err_desc = err_desc

    def __str__(self):
        return '%s: %s' % (self.__class__.__name__, DisplayAttribute.__str__(self))


class DatabaseQueryError(BaseException):
    pass

class Database(DisplayAttribute):
    def __init__(self, host, db, port=3306, user='root', passwd='123456', connect_timeout=3):
        self.host = host
        self.name = db
        self.port = port
        self.user = user
        self.passwd = passwd
        self.connect_timeout = connect_timeout
        self.connect_db()

    def connect_db(self):
        try:
            self.db = MySQLdb.connect(
                host = self.host, 
                user = self.user, 
                passwd = self.passwd, 
                db = self.name,
                port = int(self.port),
                connect_timeout = self.connect_timeout,
                charset="utf8"
            )
            self.db.autocommit(True)
            print("database connected!")
            return True
        except MySQLdb.Error, err:
            print("CONNECT TO DB FAILED! ERR INFO: %s" % (err))
            return False

    def reconnect_db(self):
        self.disconnect_db()
        return self.connect_db()

    def disconnect_db(self):
        try:
            self.db.close()
        except AttributeError, err:
            pass
        finally:
            print("database connection closed!")

    def is_db_connected(self):
        try:
            self.db.ping()
            return True
        except MySQLdb.Error, err:
            print("DB DISCONNECTED!Try to reconnect..., err info: %s" % (err))
        except AttributeError, err:
            print("DB DISCONNECTED!Try to reconnect..., err info: %s" % (err))
        return False

    def switch_db(self, userid, url_hash):
        pass

    def query(self, sql):
        result = list()
        if not self.is_db_connected():
            self.connect_db()
            if not self.is_db_connected():
                raise DatabaseQueryError()
                return result, 0
        cursor = self.db.cursor()
        try:
            rows = cursor.execute(sql)
        except MySQLdb.Error, err:
            print("execute sql error,err info:%s, sql:%s" % (err, sql))
            self.disconnect_db()
            raise DatabaseQueryError()
        result = cursor.fetchall()
        cursor.close()
        return result, rows

db_handler = Database('127.0.0.1', 'test', 3306, 'root', '123456')

def exec_sql(sql):
    try:
        db_handler.query(sql)
    except Exception as e:
        print("Exception %s, %s" % (e, sql))
   