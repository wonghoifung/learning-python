# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: consumer_register_req.proto

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
  name='consumer_register_req.proto',
  package='spider',
  syntax='proto2',
  serialized_pb=_b('\n\x1b\x63onsumer_register_req.proto\x12\x06spider\"#\n\x15\x63onsumer_register_req\x12\n\n\x02id\x18\x01 \x02(\x05')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_CONSUMER_REGISTER_REQ = _descriptor.Descriptor(
  name='consumer_register_req',
  full_name='spider.consumer_register_req',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='spider.consumer_register_req.id', index=0,
      number=1, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
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
  serialized_start=39,
  serialized_end=74,
)

DESCRIPTOR.message_types_by_name['consumer_register_req'] = _CONSUMER_REGISTER_REQ

consumer_register_req = _reflection.GeneratedProtocolMessageType('consumer_register_req', (_message.Message,), dict(
  DESCRIPTOR = _CONSUMER_REGISTER_REQ,
  __module__ = 'consumer_register_req_pb2'
  # @@protoc_insertion_point(class_scope:spider.consumer_register_req)
  ))
_sym_db.RegisterMessage(consumer_register_req)


# @@protoc_insertion_point(module_scope)
