// Auto-generated. Do not edit!

// (in-package msckf_vio.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class FeatureMeasurement {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.id = null;
      this.u0 = null;
      this.v0 = null;
      this.u1 = null;
      this.v1 = null;
    }
    else {
      if (initObj.hasOwnProperty('id')) {
        this.id = initObj.id
      }
      else {
        this.id = 0;
      }
      if (initObj.hasOwnProperty('u0')) {
        this.u0 = initObj.u0
      }
      else {
        this.u0 = 0.0;
      }
      if (initObj.hasOwnProperty('v0')) {
        this.v0 = initObj.v0
      }
      else {
        this.v0 = 0.0;
      }
      if (initObj.hasOwnProperty('u1')) {
        this.u1 = initObj.u1
      }
      else {
        this.u1 = 0.0;
      }
      if (initObj.hasOwnProperty('v1')) {
        this.v1 = initObj.v1
      }
      else {
        this.v1 = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type FeatureMeasurement
    // Serialize message field [id]
    bufferOffset = _serializer.uint64(obj.id, buffer, bufferOffset);
    // Serialize message field [u0]
    bufferOffset = _serializer.float64(obj.u0, buffer, bufferOffset);
    // Serialize message field [v0]
    bufferOffset = _serializer.float64(obj.v0, buffer, bufferOffset);
    // Serialize message field [u1]
    bufferOffset = _serializer.float64(obj.u1, buffer, bufferOffset);
    // Serialize message field [v1]
    bufferOffset = _serializer.float64(obj.v1, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type FeatureMeasurement
    let len;
    let data = new FeatureMeasurement(null);
    // Deserialize message field [id]
    data.id = _deserializer.uint64(buffer, bufferOffset);
    // Deserialize message field [u0]
    data.u0 = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [v0]
    data.v0 = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [u1]
    data.u1 = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [v1]
    data.v1 = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 40;
  }

  static datatype() {
    // Returns string type for a message object
    return 'msckf_vio/FeatureMeasurement';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'db12fb5f7b2a7982c9988e36b7a4cd3f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint64 id
    # Normalized feature coordinates (with identity intrinsic matrix)
    float64 u0 # horizontal coordinate in cam0
    float64 v0 # vertical coordinate in cam0
    float64 u1 # horizontal coordinate in cam0
    float64 v1 # vertical coordinate in cam0
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new FeatureMeasurement(null);
    if (msg.id !== undefined) {
      resolved.id = msg.id;
    }
    else {
      resolved.id = 0
    }

    if (msg.u0 !== undefined) {
      resolved.u0 = msg.u0;
    }
    else {
      resolved.u0 = 0.0
    }

    if (msg.v0 !== undefined) {
      resolved.v0 = msg.v0;
    }
    else {
      resolved.v0 = 0.0
    }

    if (msg.u1 !== undefined) {
      resolved.u1 = msg.u1;
    }
    else {
      resolved.u1 = 0.0
    }

    if (msg.v1 !== undefined) {
      resolved.v1 = msg.v1;
    }
    else {
      resolved.v1 = 0.0
    }

    return resolved;
    }
};

module.exports = FeatureMeasurement;
