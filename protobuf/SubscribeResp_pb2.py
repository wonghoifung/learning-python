# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: SubscribeResp.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='SubscribeResp.proto',
  package='',
  syntax='proto2',
  serialized_pb=_b('\n\x13SubscribeResp.proto\"A\n\rSubscribeResp\x12\x10\n\x08subReqID\x18\x01 \x02(\x05\x12\x10\n\x08respCode\x18\x02 \x02(\x05\x12\x0c\n\x04\x64\x65sc\x18\x03 \x02(\tB\x1e\n\x08\x63om.wongB\x12SubscribeRespProto')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_SUBSCRIBERESP = _descriptor.Descriptor(
  name='SubscribeResp',
  full_name='SubscribeResp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='subReqID', full_name='SubscribeResp.subReqID', index=0,
      number=1, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='respCode', full_name='SubscribeResp.respCode', index=1,
      number=2, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='desc', full_name='SubscribeResp.desc', index=2,
      number=3, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=23,
  serialized_end=88,
)

DESCRIPTOR.message_types_by_name['SubscribeResp'] = _SUBSCRIBERESP

SubscribeResp = _reflection.GeneratedProtocolMessageType('SubscribeResp', (_message.Message,), dict(
  DESCRIPTOR = _SUBSCRIBERESP,
  __module__ = 'SubscribeResp_pb2'
  # @@protoc_insertion_point(class_scope:SubscribeResp)
  ))
_sym_db.RegisterMessage(SubscribeResp)


DESCRIPTOR.has_options = True
DESCRIPTOR._options = _descriptor._ParseOptions(descriptor_pb2.FileOptions(), _b('\n\010com.wongB\022SubscribeRespProto'))
# @@protoc_insertion_point(module_scope)