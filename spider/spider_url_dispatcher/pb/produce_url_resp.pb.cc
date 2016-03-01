// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: produce_url_resp.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "produce_url_resp.pb.h"

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

const ::google::protobuf::Descriptor* produce_url_resp_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  produce_url_resp_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_produce_5furl_5fresp_2eproto() {
  protobuf_AddDesc_produce_5furl_5fresp_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "produce_url_resp.proto");
  GOOGLE_CHECK(file != NULL);
  produce_url_resp_descriptor_ = file->message_type(0);
  static const int produce_url_resp_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(produce_url_resp, res_),
  };
  produce_url_resp_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      produce_url_resp_descriptor_,
      produce_url_resp::default_instance_,
      produce_url_resp_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(produce_url_resp, _has_bits_[0]),
      -1,
      -1,
      sizeof(produce_url_resp),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(produce_url_resp, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_produce_5furl_5fresp_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      produce_url_resp_descriptor_, &produce_url_resp::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_produce_5furl_5fresp_2eproto() {
  delete produce_url_resp::default_instance_;
  delete produce_url_resp_reflection_;
}

void protobuf_AddDesc_produce_5furl_5fresp_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\026produce_url_resp.proto\022\006spider\"\037\n\020prod"
    "uce_url_resp\022\013\n\003res\030\001 \002(\005", 65);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "produce_url_resp.proto", &protobuf_RegisterTypes);
  produce_url_resp::default_instance_ = new produce_url_resp();
  produce_url_resp::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_produce_5furl_5fresp_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_produce_5furl_5fresp_2eproto {
  StaticDescriptorInitializer_produce_5furl_5fresp_2eproto() {
    protobuf_AddDesc_produce_5furl_5fresp_2eproto();
  }
} static_descriptor_initializer_produce_5furl_5fresp_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int produce_url_resp::kResFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

produce_url_resp::produce_url_resp()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:spider.produce_url_resp)
}

void produce_url_resp::InitAsDefaultInstance() {
}

produce_url_resp::produce_url_resp(const produce_url_resp& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:spider.produce_url_resp)
}

void produce_url_resp::SharedCtor() {
  _cached_size_ = 0;
  res_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

produce_url_resp::~produce_url_resp() {
  // @@protoc_insertion_point(destructor:spider.produce_url_resp)
  SharedDtor();
}

void produce_url_resp::SharedDtor() {
  if (this != default_instance_) {
  }
}

void produce_url_resp::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* produce_url_resp::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return produce_url_resp_descriptor_;
}

const produce_url_resp& produce_url_resp::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_produce_5furl_5fresp_2eproto();
  return *default_instance_;
}

produce_url_resp* produce_url_resp::default_instance_ = NULL;

produce_url_resp* produce_url_resp::New(::google::protobuf::Arena* arena) const {
  produce_url_resp* n = new produce_url_resp;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void produce_url_resp::Clear() {
  res_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool produce_url_resp::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:spider.produce_url_resp)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 res = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &res_)));
          set_has_res();
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
  // @@protoc_insertion_point(parse_success:spider.produce_url_resp)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:spider.produce_url_resp)
  return false;
#undef DO_
}

void produce_url_resp::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:spider.produce_url_resp)
  // required int32 res = 1;
  if (has_res()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->res(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:spider.produce_url_resp)
}

::google::protobuf::uint8* produce_url_resp::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:spider.produce_url_resp)
  // required int32 res = 1;
  if (has_res()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->res(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:spider.produce_url_resp)
  return target;
}

int produce_url_resp::ByteSize() const {
  int total_size = 0;

  // required int32 res = 1;
  if (has_res()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->res());
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

void produce_url_resp::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const produce_url_resp* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const produce_url_resp>(
          &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void produce_url_resp::MergeFrom(const produce_url_resp& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_res()) {
      set_res(from.res());
    }
  }
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void produce_url_resp::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void produce_url_resp::CopyFrom(const produce_url_resp& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool produce_url_resp::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void produce_url_resp::Swap(produce_url_resp* other) {
  if (other == this) return;
  InternalSwap(other);
}
void produce_url_resp::InternalSwap(produce_url_resp* other) {
  std::swap(res_, other->res_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata produce_url_resp::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = produce_url_resp_descriptor_;
  metadata.reflection = produce_url_resp_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// produce_url_resp

// required int32 res = 1;
bool produce_url_resp::has_res() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void produce_url_resp::set_has_res() {
  _has_bits_[0] |= 0x00000001u;
}
void produce_url_resp::clear_has_res() {
  _has_bits_[0] &= ~0x00000001u;
}
void produce_url_resp::clear_res() {
  res_ = 0;
  clear_has_res();
}
 ::google::protobuf::int32 produce_url_resp::res() const {
  // @@protoc_insertion_point(field_get:spider.produce_url_resp.res)
  return res_;
}
 void produce_url_resp::set_res(::google::protobuf::int32 value) {
  set_has_res();
  res_ = value;
  // @@protoc_insertion_point(field_set:spider.produce_url_resp.res)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace spider

// @@protoc_insertion_point(global_scope)