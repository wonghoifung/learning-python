// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: consumer_register_req.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "consumer_register_req.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace spider {

namespace {

const ::google::protobuf::Descriptor* consumer_register_req_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  consumer_register_req_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_consumer_5fregister_5freq_2eproto() {
  protobuf_AddDesc_consumer_5fregister_5freq_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "consumer_register_req.proto");
  GOOGLE_CHECK(file != NULL);
  consumer_register_req_descriptor_ = file->message_type(0);
  static const int consumer_register_req_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(consumer_register_req, id_),
  };
  consumer_register_req_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      consumer_register_req_descriptor_,
      consumer_register_req::default_instance_,
      consumer_register_req_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(consumer_register_req, _has_bits_[0]),
      -1,
      -1,
      sizeof(consumer_register_req),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(consumer_register_req, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_consumer_5fregister_5freq_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      consumer_register_req_descriptor_, &consumer_register_req::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_consumer_5fregister_5freq_2eproto() {
  delete consumer_register_req::default_instance_;
  delete consumer_register_req_reflection_;
}

void protobuf_AddDesc_consumer_5fregister_5freq_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\033consumer_register_req.proto\022\006spider\"#\n"
    "\025consumer_register_req\022\n\n\002id\030\001 \002(\005", 74);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "consumer_register_req.proto", &protobuf_RegisterTypes);
  consumer_register_req::default_instance_ = new consumer_register_req();
  consumer_register_req::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_consumer_5fregister_5freq_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_consumer_5fregister_5freq_2eproto {
  StaticDescriptorInitializer_consumer_5fregister_5freq_2eproto() {
    protobuf_AddDesc_consumer_5fregister_5freq_2eproto();
  }
} static_descriptor_initializer_consumer_5fregister_5freq_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int consumer_register_req::kIdFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

consumer_register_req::consumer_register_req()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:spider.consumer_register_req)
}

void consumer_register_req::InitAsDefaultInstance() {
}

consumer_register_req::consumer_register_req(const consumer_register_req& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:spider.consumer_register_req)
}

void consumer_register_req::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

consumer_register_req::~consumer_register_req() {
  // @@protoc_insertion_point(destructor:spider.consumer_register_req)
  SharedDtor();
}

void consumer_register_req::SharedDtor() {
  if (this != default_instance_) {
  }
}

void consumer_register_req::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* consumer_register_req::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return consumer_register_req_descriptor_;
}

const consumer_register_req& consumer_register_req::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_consumer_5fregister_5freq_2eproto();
  return *default_instance_;
}

consumer_register_req* consumer_register_req::default_instance_ = NULL;

consumer_register_req* consumer_register_req::New(::google::protobuf::Arena* arena) const {
  consumer_register_req* n = new consumer_register_req;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void consumer_register_req::Clear() {
  id_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool consumer_register_req::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:spider.consumer_register_req)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 id = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &id_)));
          set_has_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:spider.consumer_register_req)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:spider.consumer_register_req)
  return false;
#undef DO_
}

void consumer_register_req::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:spider.consumer_register_req)
  // required int32 id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->id(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:spider.consumer_register_req)
}

::google::protobuf::uint8* consumer_register_req::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:spider.consumer_register_req)
  // required int32 id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->id(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:spider.consumer_register_req)
  return target;
}

int consumer_register_req::ByteSize() const {
  int total_size = 0;

  // required int32 id = 1;
  if (has_id()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->id());
  }
  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void consumer_register_req::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const consumer_register_req* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const consumer_register_req>(
          &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void consumer_register_req::MergeFrom(const consumer_register_req& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
  }
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void consumer_register_req::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void consumer_register_req::CopyFrom(const consumer_register_req& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool consumer_register_req::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void consumer_register_req::Swap(consumer_register_req* other) {
  if (other == this) return;
  InternalSwap(other);
}
void consumer_register_req::InternalSwap(consumer_register_req* other) {
  std::swap(id_, other->id_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata consumer_register_req::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = consumer_register_req_descriptor_;
  metadata.reflection = consumer_register_req_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// consumer_register_req

// required int32 id = 1;
bool consumer_register_req::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void consumer_register_req::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
void consumer_register_req::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
void consumer_register_req::clear_id() {
  id_ = 0;
  clear_has_id();
}
 ::google::protobuf::int32 consumer_register_req::id() const {
  // @@protoc_insertion_point(field_get:spider.consumer_register_req.id)
  return id_;
}
 void consumer_register_req::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:spider.consumer_register_req.id)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace spider

// @@protoc_insertion_point(global_scope)