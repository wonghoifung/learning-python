# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: produce_url_req.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)




DESCRIPTOR = _descriptor.FileDescriptor(
  name='produce_url_req.proto',
  package='spider',
  serialized_pb='\n\x15produce_url_req.proto\x12\x06spider\"\x1f\n\x0fproduce_url_req\x12\x0c\n\x04urls\x18\x01 \x03(\t')




_PRODUCE_URL_REQ = _descriptor.Descriptor(
  name='produce_url_req',
  full_name='spider.produce_url_req',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='urls', full_name='spider.produce_url_req.urls', index=0,
      number=1, type=9, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
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
  extension_ranges=[],
  serialized_start=33,
  serialized_end=64,
)

DESCRIPTOR.message_types_by_name['produce_url_req'] = _PRODUCE_URL_REQ

class produce_url_req(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _PRODUCE_URL_REQ

  # @@protoc_insertion_point(class_scope:spider.produce_url_req)


# @@protoc_insertion_point(module_scope)
