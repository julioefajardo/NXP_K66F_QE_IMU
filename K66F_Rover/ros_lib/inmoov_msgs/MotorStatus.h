#ifndef _ROS_inmoov_msgs_MotorStatus_h
#define _ROS_inmoov_msgs_MotorStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace inmoov_msgs
{

  class MotorStatus : public ros::Msg
  {
    public:
      typedef const char* _joint_type;
      _joint_type joint;
      typedef uint8_t _bus_type;
      _bus_type bus;
      typedef uint8_t _id_type;
      _id_type id;
      typedef float _goal_type;
      _goal_type goal;
      typedef float _position_type;
      _position_type position;
      typedef float _presentspeed_type;
      _presentspeed_type presentspeed;
      typedef bool _moving_type;
      _moving_type moving;
      typedef uint16_t _posraw_type;
      _posraw_type posraw;
      typedef bool _enabled_type;
      _enabled_type enabled;
      typedef bool _power_type;
      _power_type power;

    MotorStatus():
      joint(""),
      bus(0),
      id(0),
      goal(0),
      position(0),
      presentspeed(0),
      moving(0),
      posraw(0),
      enabled(0),
      power(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_joint = strlen(this->joint);
      varToArr(outbuffer + offset, length_joint);
      offset += 4;
      memcpy(outbuffer + offset, this->joint, length_joint);
      offset += length_joint;
      *(outbuffer + offset + 0) = (this->bus >> (8 * 0)) & 0xFF;
      offset += sizeof(this->bus);
      *(outbuffer + offset + 0) = (this->id >> (8 * 0)) & 0xFF;
      offset += sizeof(this->id);
      union {
        float real;
        uint32_t base;
      } u_goal;
      u_goal.real = this->goal;
      *(outbuffer + offset + 0) = (u_goal.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_goal.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_goal.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_goal.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->goal);
      union {
        float real;
        uint32_t base;
      } u_position;
      u_position.real = this->position;
      *(outbuffer + offset + 0) = (u_position.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_position.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_position.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_position.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->position);
      union {
        float real;
        uint32_t base;
      } u_presentspeed;
      u_presentspeed.real = this->presentspeed;
      *(outbuffer + offset + 0) = (u_presentspeed.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_presentspeed.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_presentspeed.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_presentspeed.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->presentspeed);
      union {
        bool real;
        uint8_t base;
      } u_moving;
      u_moving.real = this->moving;
      *(outbuffer + offset + 0) = (u_moving.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->moving);
      *(outbuffer + offset + 0) = (this->posraw >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->posraw >> (8 * 1)) & 0xFF;
      offset += sizeof(this->posraw);
      union {
        bool real;
        uint8_t base;
      } u_enabled;
      u_enabled.real = this->enabled;
      *(outbuffer + offset + 0) = (u_enabled.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->enabled);
      union {
        bool real;
        uint8_t base;
      } u_power;
      u_power.real = this->power;
      *(outbuffer + offset + 0) = (u_power.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->power);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_joint;
      arrToVar(length_joint, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_joint; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_joint-1]=0;
      this->joint = (char *)(inbuffer + offset-1);
      offset += length_joint;
      this->bus =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->bus);
      this->id =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->id);
      union {
        float real;
        uint32_t base;
      } u_goal;
      u_goal.base = 0;
      u_goal.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_goal.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_goal.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_goal.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->goal = u_goal.real;
      offset += sizeof(this->goal);
      union {
        float real;
        uint32_t base;
      } u_position;
      u_position.base = 0;
      u_position.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_position.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_position.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_position.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->position = u_position.real;
      offset += sizeof(this->position);
      union {
        float real;
        uint32_t base;
      } u_presentspeed;
      u_presentspeed.base = 0;
      u_presentspeed.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_presentspeed.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_presentspeed.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_presentspeed.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->presentspeed = u_presentspeed.real;
      offset += sizeof(this->presentspeed);
      union {
        bool real;
        uint8_t base;
      } u_moving;
      u_moving.base = 0;
      u_moving.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->moving = u_moving.real;
      offset += sizeof(this->moving);
      this->posraw =  ((uint16_t) (*(inbuffer + offset)));
      this->posraw |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->posraw);
      union {
        bool real;
        uint8_t base;
      } u_enabled;
      u_enabled.base = 0;
      u_enabled.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->enabled = u_enabled.real;
      offset += sizeof(this->enabled);
      union {
        bool real;
        uint8_t base;
      } u_power;
      u_power.base = 0;
      u_power.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->power = u_power.real;
      offset += sizeof(this->power);
     return offset;
    }

    const char * getType(){ return "inmoov_msgs/MotorStatus"; };
    const char * getMD5(){ return "4d41f7c37938f0248946a636d2d6d755"; };

  };

}
#endif