// Auto-generated. Do not edit!

// (in-package msckf_vio.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class TrackingInfo {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.before_tracking = null;
      this.after_tracking = null;
      this.after_matching = null;
      this.after_ransac = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('before_tracking')) {
        this.before_tracking = initObj.before_tracking
      }
      else {
        this.before_tracking = 0;
      }
      if (initObj.hasOwnProperty('after_tracking')) {
        this.after_tracking = initObj.after_tracking
      }
      else {
        this.after_tracking = 0;
      }
      if (initObj.hasOwnProperty('after_matching')) {
        this.after_matching = initObj.after_matching
      }
      else {
        this.after_matching = 0;
      }
      if (initObj.hasOwnProperty('after_ransac')) {
        this.after_ransac = initObj.after_ransac
      }
      else {
        this.after_ransac = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type TrackingInfo
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [before_tracking]
    bufferOffset = _serializer.int16(obj.before_tracking, buffer, bufferOffset);
    // Serialize message field [after_tracking]
    bufferOffset = _serializer.int16(obj.after_tracking, buffer, bufferOffset);
    // Serialize message field [after_matching]
    bufferOffset = _serializer.int16(obj.after_matching, buffer, bufferOffset);
    // Serialize message field [after_ransac]
    bufferOffset = _serializer.int16(obj.after_ransac, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type TrackingInfo
    let len;
    let data = new TrackingInfo(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [before_tracking]
    data.before_tracking = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [after_tracking]
    data.after_tracking = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [after_matching]
    data.after_matching = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [after_ransac]
    data.after_ransac = _deserializer.int16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'msckf_vio/TrackingInfo';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'fe61515ea4754478598919b321c32c28';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Header header
    
    # Number of features after each outlier removal step.
    int16 before_tracking
    int16 after_tracking
    int16 after_matching
    int16 after_ransac
    
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    # 0: no frame
    # 1: global frame
    string frame_id
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new TrackingInfo(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.before_tracking !== undefined) {
      resolved.before_tracking = msg.before_tracking;
    }
    else {
      resolved.before_tracking = 0
    }

    if (msg.after_tracking !== undefined) {
      resolved.after_tracking = msg.after_tracking;
    }
    else {
      resolved.after_tracking = 0
    }

    if (msg.after_matching !== undefined) {
      resolved.after_matching = msg.after_matching;
    }
    else {
      resolved.after_matching = 0
    }

    if (msg.after_ransac !== undefined) {
      resolved.after_ransac = msg.after_ransac;
    }
    else {
      resolved.after_ransac = 0
    }

    return resolved;
    }
};

module.exports = TrackingInfo;
