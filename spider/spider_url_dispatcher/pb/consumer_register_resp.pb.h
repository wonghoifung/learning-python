// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: consumer_register_resp.proto

#ifndef PROTOBUF_consumer_5fregister_5fresp_2eproto__INCLUDED
#define PROTOBUF_consumer_5fregister_5fresp_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace spider {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_consumer_5fregister_5fresp_2eproto();
void protobuf_AssignDesc_consumer_5fregister_5fresp_2eproto();
void protobuf_ShutdownFile_consumer_5fregister_5fresp_2eproto();

class consumer_register_resp;

// ===================================================================

class consumer_register_resp : public ::google::protobuf::Message {
 public:
  consumer_register_resp();
  virtual ~consumer_register_resp();

  consumer_register_resp(const consumer_register_resp& from);

  inline consumer_register_resp& operator=(const consumer_register_resp& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const consumer_register_resp& default_instance();

  void Swap(consumer_register_resp* other);

  // implements Message ----------------------------------------------

  inline consumer_register_resp* New() const { return New(NULL); }

  consumer_register_resp* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const consumer_register_resp& from);
  void MergeFrom(const consumer_register_resp& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(consumer_register_resp* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 id = 1;
  bool has_id() const;
  void clear_id();
  static const int kIdFieldNumber = 1;
  ::google::protobuf::int32 id() const;
  void set_id(::google::protobuf::int32 value);

  // required int32 res = 2;
  bool has_res() const;
  void clear_res();
  static const int kResFieldNumber = 2;
  ::google::protobuf::int32 res() const;
  void set_res(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:spider.consumer_register_resp)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_res();
  inline void clear_has_res();

  // helper for ByteSize()
  int RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int32 id_;
  ::google::protobuf::int32 res_;
  friend void  protobuf_AddDesc_consumer_5fregister_5fresp_2eproto();
  friend void protobuf_AssignDesc_consumer_5fregister_5fresp_2eproto();
  friend void protobuf_ShutdownFile_consumer_5fregister_5fresp_2eproto();

  void InitAsDefaultInstance();
  static consumer_register_resp* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// consumer_register_resp

// required int32 id = 1;
inline bool consumer_register_resp::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void consumer_register_resp::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void consumer_register_resp::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void consumer_register_resp::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 consumer_register_resp::id() const {
  // @@protoc_insertion_point(field_get:spider.consumer_register_resp.id)
  return id_;
}
inline void consumer_register_resp::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:spider.consumer_register_resp.id)
}

// required int32 res = 2;
inline bool consumer_register_resp::has_res() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void consumer_register_resp::set_has_res() {
  _has_bits_[0] |= 0x00000002u;
}
inline void consumer_register_resp::clear_has_res() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void consumer_register_resp::clear_res() {
  res_ = 0;
  clear_has_res();
}
inline ::google::protobuf::int32 consumer_register_resp::res() const {
  // @@protoc_insertion_point(field_get:spider.consumer_register_resp.res)
  return res_;
}
inline void consumer_register_resp::set_res(::google::protobuf::int32 value) {
  set_has_res();
  res_ = value;
  // @@protoc_insertion_point(field_set:spider.consumer_register_resp.res)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace spider

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_consumer_5fregister_5fresp_2eproto__INCLUDED
