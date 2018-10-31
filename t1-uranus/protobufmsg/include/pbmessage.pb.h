// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: pbmessage.proto

#ifndef PROTOBUF_pbmessage_2eproto__INCLUDED
#define PROTOBUF_pbmessage_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace pbmsg {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_pbmessage_2eproto();
void protobuf_AssignDesc_pbmessage_2eproto();
void protobuf_ShutdownFile_pbmessage_2eproto();

class TMsgHeader;
class TMsgBody;
class TPBMessage;

// ===================================================================

class TMsgHeader : public ::google::protobuf::Message {
 public:
  TMsgHeader();
  virtual ~TMsgHeader();

  TMsgHeader(const TMsgHeader& from);

  inline TMsgHeader& operator=(const TMsgHeader& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const TMsgHeader& default_instance();

  void Swap(TMsgHeader* other);

  // implements Message ----------------------------------------------

  TMsgHeader* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TMsgHeader& from);
  void MergeFrom(const TMsgHeader& from);
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
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string msg_name = 1;
  inline bool has_msg_name() const;
  inline void clear_msg_name();
  static const int kMsgNameFieldNumber = 1;
  inline const ::std::string& msg_name() const;
  inline void set_msg_name(const ::std::string& value);
  inline void set_msg_name(const char* value);
  inline void set_msg_name(const char* value, size_t size);
  inline ::std::string* mutable_msg_name();
  inline ::std::string* release_msg_name();
  inline void set_allocated_msg_name(::std::string* msg_name);

  // optional uint32 seq_id = 2;
  inline bool has_seq_id() const;
  inline void clear_seq_id();
  static const int kSeqIdFieldNumber = 2;
  inline ::google::protobuf::uint32 seq_id() const;
  inline void set_seq_id(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:pbmsg.TMsgHeader)
 private:
  inline void set_has_msg_name();
  inline void clear_has_msg_name();
  inline void set_has_seq_id();
  inline void clear_has_seq_id();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* msg_name_;
  ::google::protobuf::uint32 seq_id_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_pbmessage_2eproto();
  friend void protobuf_AssignDesc_pbmessage_2eproto();
  friend void protobuf_ShutdownFile_pbmessage_2eproto();

  void InitAsDefaultInstance();
  static TMsgHeader* default_instance_;
};
// -------------------------------------------------------------------

class TMsgBody : public ::google::protobuf::Message {
 public:
  TMsgBody();
  virtual ~TMsgBody();

  TMsgBody(const TMsgBody& from);

  inline TMsgBody& operator=(const TMsgBody& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const TMsgBody& default_instance();

  void Swap(TMsgBody* other);

  // implements Message ----------------------------------------------

  TMsgBody* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TMsgBody& from);
  void MergeFrom(const TMsgBody& from);
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
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string name = 1;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 1;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // optional bytes content = 2;
  inline bool has_content() const;
  inline void clear_content();
  static const int kContentFieldNumber = 2;
  inline const ::std::string& content() const;
  inline void set_content(const ::std::string& value);
  inline void set_content(const char* value);
  inline void set_content(const void* value, size_t size);
  inline ::std::string* mutable_content();
  inline ::std::string* release_content();
  inline void set_allocated_content(::std::string* content);

  // @@protoc_insertion_point(class_scope:pbmsg.TMsgBody)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_content();
  inline void clear_has_content();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* name_;
  ::std::string* content_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_pbmessage_2eproto();
  friend void protobuf_AssignDesc_pbmessage_2eproto();
  friend void protobuf_ShutdownFile_pbmessage_2eproto();

  void InitAsDefaultInstance();
  static TMsgBody* default_instance_;
};
// -------------------------------------------------------------------

class TPBMessage : public ::google::protobuf::Message {
 public:
  TPBMessage();
  virtual ~TPBMessage();

  TPBMessage(const TPBMessage& from);

  inline TPBMessage& operator=(const TPBMessage& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const TPBMessage& default_instance();

  void Swap(TPBMessage* other);

  // implements Message ----------------------------------------------

  TPBMessage* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TPBMessage& from);
  void MergeFrom(const TPBMessage& from);
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
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional .pbmsg.TMsgHeader header = 1;
  inline bool has_header() const;
  inline void clear_header();
  static const int kHeaderFieldNumber = 1;
  inline const ::pbmsg::TMsgHeader& header() const;
  inline ::pbmsg::TMsgHeader* mutable_header();
  inline ::pbmsg::TMsgHeader* release_header();
  inline void set_allocated_header(::pbmsg::TMsgHeader* header);

  // repeated .pbmsg.TMsgBody body = 2;
  inline int body_size() const;
  inline void clear_body();
  static const int kBodyFieldNumber = 2;
  inline const ::pbmsg::TMsgBody& body(int index) const;
  inline ::pbmsg::TMsgBody* mutable_body(int index);
  inline ::pbmsg::TMsgBody* add_body();
  inline const ::google::protobuf::RepeatedPtrField< ::pbmsg::TMsgBody >&
      body() const;
  inline ::google::protobuf::RepeatedPtrField< ::pbmsg::TMsgBody >*
      mutable_body();

  // @@protoc_insertion_point(class_scope:pbmsg.TPBMessage)
 private:
  inline void set_has_header();
  inline void clear_has_header();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::pbmsg::TMsgHeader* header_;
  ::google::protobuf::RepeatedPtrField< ::pbmsg::TMsgBody > body_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_pbmessage_2eproto();
  friend void protobuf_AssignDesc_pbmessage_2eproto();
  friend void protobuf_ShutdownFile_pbmessage_2eproto();

  void InitAsDefaultInstance();
  static TPBMessage* default_instance_;
};
// ===================================================================


// ===================================================================

// TMsgHeader

// optional string msg_name = 1;
inline bool TMsgHeader::has_msg_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TMsgHeader::set_has_msg_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TMsgHeader::clear_has_msg_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TMsgHeader::clear_msg_name() {
  if (msg_name_ != &::google::protobuf::internal::kEmptyString) {
    msg_name_->clear();
  }
  clear_has_msg_name();
}
inline const ::std::string& TMsgHeader::msg_name() const {
  return *msg_name_;
}
inline void TMsgHeader::set_msg_name(const ::std::string& value) {
  set_has_msg_name();
  if (msg_name_ == &::google::protobuf::internal::kEmptyString) {
    msg_name_ = new ::std::string;
  }
  msg_name_->assign(value);
}
inline void TMsgHeader::set_msg_name(const char* value) {
  set_has_msg_name();
  if (msg_name_ == &::google::protobuf::internal::kEmptyString) {
    msg_name_ = new ::std::string;
  }
  msg_name_->assign(value);
}
inline void TMsgHeader::set_msg_name(const char* value, size_t size) {
  set_has_msg_name();
  if (msg_name_ == &::google::protobuf::internal::kEmptyString) {
    msg_name_ = new ::std::string;
  }
  msg_name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* TMsgHeader::mutable_msg_name() {
  set_has_msg_name();
  if (msg_name_ == &::google::protobuf::internal::kEmptyString) {
    msg_name_ = new ::std::string;
  }
  return msg_name_;
}
inline ::std::string* TMsgHeader::release_msg_name() {
  clear_has_msg_name();
  if (msg_name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = msg_name_;
    msg_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void TMsgHeader::set_allocated_msg_name(::std::string* msg_name) {
  if (msg_name_ != &::google::protobuf::internal::kEmptyString) {
    delete msg_name_;
  }
  if (msg_name) {
    set_has_msg_name();
    msg_name_ = msg_name;
  } else {
    clear_has_msg_name();
    msg_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional uint32 seq_id = 2;
inline bool TMsgHeader::has_seq_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TMsgHeader::set_has_seq_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TMsgHeader::clear_has_seq_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TMsgHeader::clear_seq_id() {
  seq_id_ = 0u;
  clear_has_seq_id();
}
inline ::google::protobuf::uint32 TMsgHeader::seq_id() const {
  return seq_id_;
}
inline void TMsgHeader::set_seq_id(::google::protobuf::uint32 value) {
  set_has_seq_id();
  seq_id_ = value;
}

// -------------------------------------------------------------------

// TMsgBody

// optional string name = 1;
inline bool TMsgBody::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TMsgBody::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TMsgBody::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TMsgBody::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& TMsgBody::name() const {
  return *name_;
}
inline void TMsgBody::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void TMsgBody::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void TMsgBody::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* TMsgBody::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* TMsgBody::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void TMsgBody::set_allocated_name(::std::string* name) {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    delete name_;
  }
  if (name) {
    set_has_name();
    name_ = name;
  } else {
    clear_has_name();
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional bytes content = 2;
inline bool TMsgBody::has_content() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TMsgBody::set_has_content() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TMsgBody::clear_has_content() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TMsgBody::clear_content() {
  if (content_ != &::google::protobuf::internal::kEmptyString) {
    content_->clear();
  }
  clear_has_content();
}
inline const ::std::string& TMsgBody::content() const {
  return *content_;
}
inline void TMsgBody::set_content(const ::std::string& value) {
  set_has_content();
  if (content_ == &::google::protobuf::internal::kEmptyString) {
    content_ = new ::std::string;
  }
  content_->assign(value);
}
inline void TMsgBody::set_content(const char* value) {
  set_has_content();
  if (content_ == &::google::protobuf::internal::kEmptyString) {
    content_ = new ::std::string;
  }
  content_->assign(value);
}
inline void TMsgBody::set_content(const void* value, size_t size) {
  set_has_content();
  if (content_ == &::google::protobuf::internal::kEmptyString) {
    content_ = new ::std::string;
  }
  content_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* TMsgBody::mutable_content() {
  set_has_content();
  if (content_ == &::google::protobuf::internal::kEmptyString) {
    content_ = new ::std::string;
  }
  return content_;
}
inline ::std::string* TMsgBody::release_content() {
  clear_has_content();
  if (content_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = content_;
    content_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void TMsgBody::set_allocated_content(::std::string* content) {
  if (content_ != &::google::protobuf::internal::kEmptyString) {
    delete content_;
  }
  if (content) {
    set_has_content();
    content_ = content;
  } else {
    clear_has_content();
    content_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// TPBMessage

// optional .pbmsg.TMsgHeader header = 1;
inline bool TPBMessage::has_header() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TPBMessage::set_has_header() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TPBMessage::clear_has_header() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TPBMessage::clear_header() {
  if (header_ != NULL) header_->::pbmsg::TMsgHeader::Clear();
  clear_has_header();
}
inline const ::pbmsg::TMsgHeader& TPBMessage::header() const {
  return header_ != NULL ? *header_ : *default_instance_->header_;
}
inline ::pbmsg::TMsgHeader* TPBMessage::mutable_header() {
  set_has_header();
  if (header_ == NULL) header_ = new ::pbmsg::TMsgHeader;
  return header_;
}
inline ::pbmsg::TMsgHeader* TPBMessage::release_header() {
  clear_has_header();
  ::pbmsg::TMsgHeader* temp = header_;
  header_ = NULL;
  return temp;
}
inline void TPBMessage::set_allocated_header(::pbmsg::TMsgHeader* header) {
  delete header_;
  header_ = header;
  if (header) {
    set_has_header();
  } else {
    clear_has_header();
  }
}

// repeated .pbmsg.TMsgBody body = 2;
inline int TPBMessage::body_size() const {
  return body_.size();
}
inline void TPBMessage::clear_body() {
  body_.Clear();
}
inline const ::pbmsg::TMsgBody& TPBMessage::body(int index) const {
  return body_.Get(index);
}
inline ::pbmsg::TMsgBody* TPBMessage::mutable_body(int index) {
  return body_.Mutable(index);
}
inline ::pbmsg::TMsgBody* TPBMessage::add_body() {
  return body_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pbmsg::TMsgBody >&
TPBMessage::body() const {
  return body_;
}
inline ::google::protobuf::RepeatedPtrField< ::pbmsg::TMsgBody >*
TPBMessage::mutable_body() {
  return &body_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pbmsg

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_pbmessage_2eproto__INCLUDED
