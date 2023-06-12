/*******************************************************************
*
*  DESCRIPTION: Atomic Model Tracking_Table
*
*  AUTHOR: Peter MacSweem 
*
*  DATE: 17/10/2003
*
*******************************************************************/

#ifndef __TRACKING_TABLE_H
#define __TRACKING_TABLE_H

#include <list>
#include "atomic.h"     // class Atomic

class Tracking_Table : public Atomic
{
public:
	Tracking_Table( const string &name = "Tracking_Table" );	//Default constructor

	virtual string className() const ;
protected:

  enum trtab_state // Set local state definitions (S)
  {
    wait,
    receive_update_from_bus,
    notify_new_freq,
    new_signal_detected,
    send_update_to_bus
  } ;

  Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:

  const Port &signal_props;
  const Port &bus_receive_freq;
  const Port &bus_receive_id;
  Port &bus_send_id;
  Port &bus_send_freq;
  Port &new_freq;

  Time updateTime;
  Time procTime;
  Time busTime;
  Time notifyTime;

  trtab_state localState;
  Value tableID;
  Value update_freq;

};	// class Tracking_Table

// ** inline ** // 
inline
string Tracking_Table::className() const
{
	return "Tracking_Table" ;
}

#endif   //__TRACKING_TABLE_H
