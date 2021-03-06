// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: consume_url_req.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "consume_url_req.pb.h"

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

const ::google::protobuf::Descriptor* consume_url_req_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  consume_url_req_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_consume_5furl_5freq_2eproto() {
  protobuf_AddDesc_consume_5furl_5freq_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "consume_url_req.proto");
  GOOGLE_CHECK(file != NULL);
  consume_url_req_descriptor_ = file->message_type(0);
  static const int consume_url_req_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(consume_url_req, urls_),
  };
  consume_url_req_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      consume_url_req_descriptor_,
      consume_url_req::default_instance_,
      consume_url_req_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(consume_url_req, _has_bits_[0]),
      -1,
      -1,
      sizeof(consume_url_req),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(consume_url_req, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_consume_5furl_5freq_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      consume_url_req_descriptor_, &consume_url_req::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_consume_5furl_5freq_2eproto() {
  delete consume_url_req::default_instance_;
  delete consume_url_req_reflection_;
}

void protobuf_AddDesc_consume_5furl_5freq_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\025consume_url_req.proto\022\006spider\"\037\n\017consu"
    "me_url_req\022\014\n\004urls\030\001 \003(\t", 64);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "consume_url_req.proto", &protobuf_RegisterTypes);
  consume_url_req::default_instance_ = new consume_url_req();
  consume_url_req::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_consume_5furl_5freq_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_consume_5furl_5freq_2eproto {
  StaticDescriptorInitializer_consume_5furl_5freq_2eproto() {
    protobuf_AddDesc_consume_5furl_5freq_2eproto();
  }
} static_descriptor_initializer_consume_5furl_5freq_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int consume_url_req::kUrlsFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

consume_url_req::consume_url_req()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:spider.consume_url_req)
}

void consume_url_req::InitAsDefaultInstance() {
}

consume_url_req::consume_url_req(const consume_url_req& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:spider.consume_url_req)
}

void consume_url_req::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

consume_url_req::~consume_url_req() {
  // @@protoc_insertion_point(destructor:spider.consume_url_req)
  SharedDtor();
}

void consume_url_req::SharedDtor() {
  if (this != default_instance_) {
  }
}

void consume_url_req::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* consume_url_req::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return consume_url_req_descriptor_;
}

const consume_url_req& consume_url_req::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_consume_5furl_5freq_2eproto();
  return *default_instance_;
}

consume_url_req* consume_url_req::default_instance_ = NULL;

consume_url_req* consume_url_req::New(::google::protobuf::Arena* arena) const {
  consume_url_req* n = new consume_url_req;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void consume_url_req::Clear() {
  urls_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool consume_url_req::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:spider.consume_url_req)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated string urls = 1;
      case 1: {
        if (tag == 10) {
         parse_urls:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->add_urls()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->urls(this->urls_size() - 1).data(),
            this->urls(this->urls_size() - 1).length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "spider.consume_url_req.urls");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_urls;
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
  // @@protoc_insertion_point(parse_success:spider.consume_url_req)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:spider.consume_url_req)
  return false;
#undef DO_
}

void consume_url_req::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:spider.consume_url_req)
  // repeated string urls = 1;
  for (int i = 0; i < this->urls_size(); i++) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->urls(i).data(), this->urls(i).length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "spider.consume_url_req.urls");
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->urls(i), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:spider.consume_url_req)
}

::google::protobuf::uint8* consume_url_req::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:spider.consume_url_req)
  // repeated string urls = 1;
  for (int i = 0; i < this->urls_size(); i++) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->urls(i).data(), this->urls(i).length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "spider.consume_url_req.urls");
    target = ::google::protobuf::internal::WireFormatLite::
      WriteStringToArray(1, this->urls(i), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:spider.consume_url_req)
  return target;
}

int consume_url_req::ByteSize() const {
  int total_size = 0;

  // repeated string urls = 1;
  total_size += 1 * this->urls_size();
  for (int i = 0; i < this->urls_size(); i++) {
    total_size += ::google::protobuf::internal::WireFormatLite::StringSize(
      this->urls(i));
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

void consume_url_req::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const consume_url_req* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const consume_url_req>(
          &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void consume_url_req::MergeFrom(const consume_url_req& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  urls_.MergeFrom(from.urls_);
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void consume_url_req::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void consume_url_req::CopyFrom(const consume_url_req& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool consume_url_req::IsInitialized() const {

  return true;
}

void consume_url_req::Swap(consume_url_req* other) {
  if (other == this) return;
  InternalSwap(other);
}
void consume_url_req::InternalSwap(consume_url_req* other) {
  urls_.UnsafeArenaSwap(&other->urls_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata consume_url_req::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = consume_url_req_descriptor_;
  metadata.reflection = consume_url_req_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// consume_url_req

// repeated string urls = 1;
int consume_url_req::urls_size() const {
  return urls_.size();
}
void consume_url_req::clear_urls() {
  urls_.Clear();
}
 const ::std::string& consume_url_req::urls(int index) const {
  // @@protoc_insertion_point(field_get:spider.consume_url_req.urls)
  return urls_.Get(index);
}
 ::std::string* consume_url_req::mutable_urls(int index) {
  // @@protoc_insertion_point(field_mutable:spider.consume_url_req.urls)
  return urls_.Mutable(index);
}
 void consume_url_req::set_urls(int index, const ::std::string& value) {
  // @@protoc_insertion_point(field_set:spider.consume_url_req.urls)
  urls_.Mutable(index)->assign(value);
}
 void consume_url_req::set_urls(int index, const char* value) {
  urls_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:spider.consume_url_req.urls)
}
 void consume_url_req::set_urls(int index, const char* value, size_t size) {
  urls_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:spider.consume_url_req.urls)
}
 ::std::string* consume_url_req::add_urls() {
  return urls_.Add();
}
 void consume_url_req::add_urls(const ::std::string& value) {
  urls_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:spider.consume_url_req.urls)
}
 void consume_url_req::add_urls(const char* value) {
  urls_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:spider.consume_url_req.urls)
}
 void consume_url_req::add_urls(const char* value, size_t size) {
  urls_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:spider.consume_url_req.urls)
}
 const ::google::protobuf::RepeatedPtrField< ::std::string>&
consume_url_req::urls() const {
  // @@protoc_insertion_point(field_list:spider.consume_url_req.urls)
  return urls_;
}
 ::google::protobuf::RepeatedPtrField< ::std::string>*
consume_url_req::mutable_urls() {
  // @@protoc_insertion_point(field_mutable_list:spider.consume_url_req.urls)
  return &urls_;
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace spider

// @@protoc_insertion_point(global_scope)
