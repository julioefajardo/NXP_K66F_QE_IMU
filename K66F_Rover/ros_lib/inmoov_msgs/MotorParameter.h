#ifndef _ROS_SERVICE_MotorParameter_h
#define _ROS_SERVICE_MotorParameter_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace inmoov_msgs
{

static const char MOTORPARAMETER[] = "inmoov_msgs/MotorParameter";

  class MotorParameterRequest : public ros::Msg
  {
    public:
      typedef uint8_t _id_type;
      _id_type id;
      typedef uint8_t _parameter_type;
      _parameter_type parameter;

    MotorParameterRequest():
      id(0),
      parameter(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->id >> (8 * 0)) & 0xFF;
      offset += sizeof(this->id);
      *(outbuffer + offset + 0) = (this->parameter >> (8 * 0)) & 0xFF;
      offset += sizeof(this->parameter);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->id =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->id);
      this->parameter =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->parameter);
     return offset;
    }

    const char * getType(){ return MOTORPARAMETER; };
    const char * getMD5(){ return "e50bd98c68b747be3e6ef47cccff3aad"; };

  };

  class MotorParameterResponse : public ros::Msg
  {
    public:
      typedef float _data_type;
      _data_type data;

    MotorParameterResponse():
      data(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_data;
      u_data.real = this->data;
      *(outbuffer + offset + 0) = (u_data.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_data.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_data.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_data.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->data);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_data;
      u_data.base = 0;
      u_data.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_data.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_data.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_data.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->data = u_data.real;
      offset += sizeof(this->data);
     return offset;
    }

    const char * getType(){ return MOTORPARAMETER; };
    const char * getMD5(){ return "73fcbf46b49191e672908e50842a83d4"; };

  };

  class MotorParameter {
    public:
    typedef MotorParameterRequest Request;
    typedef MotorParameterResponse Response;
  };

}
#endif
