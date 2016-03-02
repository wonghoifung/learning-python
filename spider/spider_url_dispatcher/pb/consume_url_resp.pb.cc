// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: consume_url_resp.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "consume_url_resp.pb.h"

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

const ::google::protobuf::Descriptor* consume_url_resp_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  consume_url_resp_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_consume_5furl_5fresp_2eproto() {
  protobuf_AddDesc_consume_5furl_5fresp_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "consume_url_resp.proto");
  GOOGLE_CHECK(file != NULL);
  consume_url_resp_descriptor_ = file->message_type(0);
  static const int consume_url_resp_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(consume_url_resp, res_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(consume_url_resp, failed_urls_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(consume_url_resp, success_urls_),
  };
  consume_url_resp_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      consume_url_resp_descriptor_,
      consume_url_resp::default_instance_,
      consume_url_resp_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(consume_url_resp, _has_bits_[0]),
      -1,
      -1,
      sizeof(consume_url_resp),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(consume_url_resp, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_consume_5furl_5fresp_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      consume_url_resp_descriptor_, &consume_url_resp::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_consume_5furl_5fresp_2eproto() {
  delete consume_url_resp::default_instance_;
  delete consume_url_resp_reflection_;
}

void protobuf_AddDesc_consume_5furl_5fresp_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\026consume_url_resp.proto\022\006spider\"J\n\020cons"
    "ume_url_resp\022\013\n\003res\030\001 \002(\005\022\023\n\013failed_urls"
    "\030\002 \003(\t\022\024\n\014success_urls\030\003 \003(\t", 108);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "consume_url_resp.proto", &protobuf_RegisterTypes);
  consume_url_resp::default_instance_ = new consume_url_resp();
  consume_url_resp::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_consume_5furl_5fresp_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_consume_5furl_5fresp_2eproto {
  StaticDescriptorInitializer_consume_5furl_5fresp_2eproto() {
    protobuf_AddDesc_consume_5furl_5fresp_2eproto();
  }
} static_descriptor_initializer_consume_5furl_5fresp_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int consume_url_resp::kResFieldNumber;
const int consume_url_resp::kFailedUrlsFieldNumber;
const int consume_url_resp::kSuccessUrlsFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

consume_url_resp::consume_url_resp()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:spider.consume_url_resp)
}

void consume_url_resp::InitAsDefaultInstance() {
}

consume_url_resp::consume_url_resp(const consume_url_resp& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:spider.consume_url_resp)
}

void consume_url_resp::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  res_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

consume_url_resp::~consume_url_resp() {
  // @@protoc_insertion_point(destructor:spider.consume_url_resp)
  SharedDtor();
}

void consume_url_resp::SharedDtor() {
  if (this != default_instance_) {
  }
}

void consume_url_resp::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* consume_url_resp::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return consume_url_resp_descriptor_;
}

const consume_url_resp& consume_url_resp::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_consume_5furl_5fresp_2eproto();
  return *default_instance_;
}

consume_url_resp* consume_url_resp::default_instance_ = NULL;

consume_url_resp* consume_url_resp::New(::google::protobuf::Arena* arena) const {
  consume_url_resp* n = new consume_url_resp;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void consume_url_resp::Clear() {
  res_ = 0;
  failed_urls_.Clear();
  success_urls_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool consume_url_resp::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:spider.consume_url_resp)
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
        if (input->ExpectTag(18)) goto parse_failed_urls;
        break;
      }

      // repeated string failed_urls = 2;
      case 2: {
        if (tag == 18) {
         parse_failed_urls:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->add_failed_urls()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->failed_urls(this->failed_urls_size() - 1).data(),
            this->failed_urls(this->failed_urls_size() - 1).length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "spider.consume_url_resp.failed_urls");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_failed_urls;
        if (input->ExpectTag(26)) goto parse_success_urls;
        break;
      }

      // repeated string success_urls = 3;
      case 3: {
        if (tag == 26) {
         parse_success_urls:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->add_success_urls()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->success_urls(this->success_urls_size() - 1).data(),
            this->success_urls(this->success_urls_size() - 1).length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "spider.consume_url_resp.success_urls");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_success_urls;
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
  // @@protoc_insertion_point(parse_success:spider.consume_url_resp)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:spider.consume_url_resp)
  return false;
#undef DO_
}

void consume_url_resp::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:spider.consume_url_resp)
  // required int32 res = 1;
  if (has_res()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->res(), output);
  }

  // repeated string failed_urls = 2;
  for (int i = 0; i < this->failed_urls_size(); i++) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->failed_urls(i).data(), this->failed_urls(i).length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "spider.consume_url_resp.failed_urls");
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->failed_urls(i), output);
  }

  // repeated string success_urls = 3;
  for (int i = 0; i < this->success_urls_size(); i++) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->success_urls(i).data(), this->success_urls(i).length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "spider.consume_url_resp.success_urls");
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->success_urls(i), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:spider.consume_url_resp)
}

::google::protobuf::uint8* consume_url_resp::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:spider.consume_url_resp)
  // required int32 res = 1;
  if (has_res()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->res(), target);
  }

  // repeated string failed_urls = 2;
  for (int i = 0; i < this->failed_urls_size(); i++) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->failed_urls(i).data(), this->failed_urls(i).length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "spider.consume_url_resp.failed_urls");
    target = ::google::protobuf::internal::WireFormatLite::
      WriteStringToArray(2, this->failed_urls(i), target);
  }

  // repeated string success_urls = 3;
  for (int i = 0; i < this->success_urls_size(); i++) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->success_urls(i).data(), this->success_urls(i).length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "spider.consume_url_resp.success_urls");
    target = ::google::protobuf::internal::WireFormatLite::
      WriteStringToArray(3, this->success_urls(i), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:spider.consume_url_resp)
  return target;
}

int consume_url_resp::ByteSize() const {
  int total_size = 0;

  // required int32 res = 1;
  if (has_res()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->res());
  }
  // repeated string failed_urls = 2;
  total_size += 1 * this->failed_urls_size();
  for (int i = 0; i < this->failed_urls_size(); i++) {
    total_size += ::google::protobuf::internal::WireFormatLite::StringSize(
      this->failed_urls(i));
  }

  // repeated string success_urls = 3;
  total_size += 1 * this->success_urls_size();
  for (int i = 0; i < this->success_urls_size(); i++) {
    total_size += ::google::protobuf::internal::WireFormatLite::StringSize(
      this->success_urls(i));
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

void consume_url_resp::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const consume_url_resp* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const consume_url_resp>(
          &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void consume_url_resp::MergeFrom(const consume_url_resp& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  failed_urls_.MergeFrom(from.failed_urls_);
  success_urls_.MergeFrom(from.success_urls_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_res()) {
      set_res(from.res());
    }
  }
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void consume_url_resp::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void consume_url_resp::CopyFrom(const consume_url_resp& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool consume_url_resp::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void consume_url_resp::Swap(consume_url_resp* other) {
  if (other == this) return;
  InternalSwap(other);
}
void consume_url_resp::InternalSwap(consume_url_resp* other) {
  std::swap(res_, other->res_);
  failed_urls_.UnsafeArenaSwap(&other->failed_urls_);
  success_urls_.UnsafeArenaSwap(&other->success_urls_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata consume_url_resp::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = consume_url_resp_descriptor_;
  metadata.reflection = consume_url_resp_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// consume_url_resp

// required int32 res = 1;
bool consume_url_resp::has_res() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void consume_url_resp::set_has_res() {
  _has_bits_[0] |= 0x00000001u;
}
void consume_url_resp::clear_has_res() {
  _has_bits_[0] &= ~0x00000001u;
}
void consume_url_resp::clear_res() {
  res_ = 0;
  clear_has_res();
}
 ::google::protobuf::int32 consume_url_resp::res() const {
  // @@protoc_insertion_point(field_get:spider.consume_url_resp.res)
  return res_;
}
 void consume_url_resp::set_res(::google::protobuf::int32 value) {
  set_has_res();
  res_ = value;
  // @@protoc_insertion_point(field_set:spider.consume_url_resp.res)
}

// repeated string failed_urls = 2;
int consume_url_resp::failed_urls_size() const {
  return failed_urls_.size();
}
void consume_url_resp::clear_failed_urls() {
  failed_urls_.Clear();
}
 const ::std::string& consume_url_resp::failed_urls(int index) const {
  // @@protoc_insertion_point(field_get:spider.consume_url_resp.failed_urls)
  return failed_urls_.Get(index);
}
 ::std::string* consume_url_resp::mutable_failed_urls(int index) {
  // @@protoc_insertion_point(field_mutable:spider.consume_url_resp.failed_urls)
  return failed_urls_.Mutable(index);
}
 void consume_url_resp::set_failed_urls(int index, const ::std::string& value) {
  // @@protoc_insertion_point(field_set:spider.consume_url_resp.failed_urls)
  failed_urls_.Mutable(index)->assign(value);
}
 void consume_url_resp::set_failed_urls(int index, const char* value) {
  failed_urls_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:spider.consume_url_resp.failed_urls)
}
 void consume_url_resp::set_failed_urls(int index, const char* value, size_t size) {
  failed_urls_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:spider.consume_url_resp.failed_urls)
}
 ::std::string* consume_url_resp::add_failed_urls() {
  return failed_urls_.Add();
}
 void consume_url_resp::add_failed_urls(const ::std::string& value) {
  failed_urls_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:spider.consume_url_resp.failed_urls)
}
 void consume_url_resp::add_failed_urls(const char* value) {
  failed_urls_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:spider.consume_url_resp.failed_urls)
}
 void consume_url_resp::add_failed_urls(const char* value, size_t size) {
  failed_urls_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:spider.consume_url_resp.failed_urls)
}
 const ::google::protobuf::RepeatedPtrField< ::std::string>&
consume_url_resp::failed_urls() const {
  // @@protoc_insertion_point(field_list:spider.consume_url_resp.failed_urls)
  return failed_urls_;
}
 ::google::protobuf::RepeatedPtrField< ::std::string>*
consume_url_resp::mutable_failed_urls() {
  // @@protoc_insertion_point(field_mutable_list:spider.consume_url_resp.failed_urls)
  return &failed_urls_;
}

// repeated string success_urls = 3;
int consume_url_resp::success_urls_size() const {
  return success_urls_.size();
}
void consume_url_resp::clear_success_urls() {
  success_urls_.Clear();
}
 const ::std::string& consume_url_resp::success_urls(int index) const {
  // @@protoc_insertion_point(field_get:spider.consume_url_resp.success_urls)
  return success_urls_.Get(index);
}
 ::std::string* consume_url_resp::mutable_success_urls(int index) {
  // @@protoc_insertion_point(field_mutable:spider.consume_url_resp.success_urls)
  return success_urls_.Mutable(index);
}
 void consume_url_resp::set_success_urls(int index, const ::std::string& value) {
  // @@protoc_insertion_point(field_set:spider.consume_url_resp.success_urls)
  success_urls_.Mutable(index)->assign(value);
}
 void consume_url_resp::set_success_urls(int index, const char* value) {
  success_urls_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:spider.consume_url_resp.success_urls)
}
 void consume_url_resp::set_success_urls(int index, const char* value, size_t size) {
  success_urls_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:spider.consume_url_resp.success_urls)
}
 ::std::string* consume_url_resp::add_success_urls() {
  return success_urls_.Add();
}
 void consume_url_resp::add_success_urls(const ::std::string& value) {
  success_urls_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:spider.consume_url_resp.success_urls)
}
 void consume_url_resp::add_success_urls(const char* value) {
  success_urls_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:spider.consume_url_resp.success_urls)
}
 void consume_url_resp::add_success_urls(const char* value, size_t size) {
  success_urls_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:spider.consume_url_resp.success_urls)
}
 const ::google::protobuf::RepeatedPtrField< ::std::string>&
consume_url_resp::success_urls() const {
  // @@protoc_insertion_point(field_list:spider.consume_url_resp.success_urls)
  return success_urls_;
}
 ::google::protobuf::RepeatedPtrField< ::std::string>*
consume_url_resp::mutable_success_urls() {
  // @@protoc_insertion_point(field_mutable_list:spider.consume_url_resp.success_urls)
  return &success_urls_;
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace spider

// @@protoc_insertion_point(global_scope)
