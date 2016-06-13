/**************************************************************************
  Copyright (c) 2013, 2014, 2015 Rockwell Collins and the University of Minnesota.
  Developed with the sponsorship of the Defense Advanced Research Projects Agency (DARPA).

  Permission is hereby granted, free of charge, to any person obtaining a copy of this data,
  including any software or models in source or binary form, as well as any drawings, specifications, 
  and documentation (collectively "the Data"), to deal in the Data without restriction, including 
  without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
  and/or sell copies of the Data, and to permit persons to whom the Data is furnished to do so, 
  subject to the following conditions: 

  The above copyright notice and this permission notice shall be included in all copies or
  substantial portions of the Data.

  THE DATA IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
  LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
  IN NO EVENT SHALL THE AUTHORS, SPONSORS, DEVELOPERS, CONTRIBUTORS, OR COPYRIGHT HOLDERS BE LIABLE 
  FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
  ARISING FROM, OUT OF OR IN CONNECTION WITH THE DATA OR THE USE OR OTHER DEALINGS IN THE DATA. 

 **************************************************************************/


/**************************************************************************

   File: /home/john/git/smaccm/models/SmaccmPhaseIIIV2/components/Server/src/smaccm_Server.c
   Created on: 2016/06/13 16:20:10
   using Dulcimer AADL system build tool suite 

   ***AUTOGENERATED CODE: DO NOT MODIFY***

  This C file contains the implementations of the AADL primitives
  used by user-level declarations for thread Server.   

  The user code runs in terms of "dispatchers", which cause 
  dispatch user-level handlers to execute.  These handlers can 
  communicate using the standard AADL primitives, which are mapped
  to C functions.

  The send/receive handlers are not thread safe in CAmkES; it is 
  assumed that this is handled by the CAmkES sequentialized access 
  to the dispatch handler.  There is only one dispatch interface 
  for the component containing all of the dispatch points.

  They are thread safe for eChronos.

  The read/write handlers are thread safe because the writer comes 
  through a dispatch interface but the reader is "local" on a dispatch
  interface and so contention may occur.


 **************************************************************************/
#include <smaccm_Server.h>
#include <string.h>
#include <Server.h>

///////////////////////////////////////////////////////////////////////////
//
// Local prototypes for AADL dispatchers
//
///////////////////////////////////////////////////////////////////////////
static void 
smaccm_Server_periodic_dispatcher_dispatcher(int64_t * periodic_dispatcher); 
static void 
smaccm_Server_Server_initializer_dispatcher(int64_t * Server_initializer); 
static void 
smaccm_Server_get_input_dispatcher(SMACCM_DATA__Array_U8_80 get_input); 
static void 
smaccm_Server_get_can_dispatcher(SMACCM_DATA__Array_U8_80 get_can); 
 
 



/************************************************************************
 * 
 * Static variables and queue management functions for port:
 * 	get_input
 * 
 ************************************************************************/

static SMACCM_DATA__Array_U8_80 smaccm_queue_get_input [1];
static bool smaccm_queue_full_get_input  = false;
static uint32_t smaccm_queue_front_get_input  = 0;
static uint32_t smaccm_queue_back_get_input  = 0;

bool smaccm_queue_is_full_get_input() {
	return (smaccm_queue_front_get_input == smaccm_queue_back_get_input) && (smaccm_queue_full_get_input);
}

bool smaccm_queue_is_empty_get_input() {
	return (smaccm_queue_front_get_input == smaccm_queue_back_get_input) && (!smaccm_queue_full_get_input); 
}

bool smaccm_queue_read_get_input(SMACCM_DATA__Array_U8_80 get_input) {
	if (smaccm_queue_is_empty_get_input()) {
		return false;
	} else {
		memcpy(get_input, smaccm_queue_get_input[smaccm_queue_back_get_input], sizeof(SMACCM_DATA__Array_U8_80));

		smaccm_queue_back_get_input = (smaccm_queue_back_get_input + 1) % 1; 
		smaccm_queue_full_get_input = false ; 
		return true;
	}
}

bool smaccm_queue_write_get_input(const SMACCM_DATA__Array_U8_80 get_input) {
	if (smaccm_queue_is_full_get_input()) {
		return false;
	} else {
		memcpy(smaccm_queue_get_input[smaccm_queue_front_get_input], get_input, sizeof(SMACCM_DATA__Array_U8_80));

		smaccm_queue_front_get_input = (smaccm_queue_front_get_input + 1) % 1; 		
		if (smaccm_queue_back_get_input == smaccm_queue_front_get_input) { 
			smaccm_queue_full_get_input = true ; 
		}
		return true;
	}
}

/************************************************************************
 *  get_input_write_SMACCM_DATA__Array_U8_80: 
 * Invoked by: remote interface.
 * 
 * This is the function invoked by a remote RPC to write to an active-thread
 * input event data port.  It queues the input message into a circular buffer.
 * 
 ************************************************************************/

bool get_input_write_SMACCM_DATA__Array_U8_80(const smaccm_SMACCM_DATA__Array_U8_80_container * arg) {
	bool result;
	smaccm_server_get_input_mut_lock(); 
	result = smaccm_queue_write_get_input((uint8_t *) arg);
	smaccm_server_get_input_mut_unlock(); 
	return result;
}


/************************************************************************
 *  Server_read_get_input: 
 * Invoked from local active thread.
 * 
 * This is the function invoked by the active thread to read from the 
 * input event data queue circular buffer.
 * 
 ************************************************************************/

bool Server_read_get_input(SMACCM_DATA__Array_U8_80 arg) {
	bool result; 
	smaccm_server_get_input_mut_lock(); 
	result = smaccm_queue_read_get_input(arg);
	smaccm_server_get_input_mut_unlock(); 
	return result;
}


/************************************************************************
 * 
 * Static variables and queue management functions for port:
 * 	get_can
 * 
 ************************************************************************/

static SMACCM_DATA__Array_U8_80 smaccm_queue_get_can [1];
static bool smaccm_queue_full_get_can  = false;
static uint32_t smaccm_queue_front_get_can  = 0;
static uint32_t smaccm_queue_back_get_can  = 0;

bool smaccm_queue_is_full_get_can() {
	return (smaccm_queue_front_get_can == smaccm_queue_back_get_can) && (smaccm_queue_full_get_can);
}

bool smaccm_queue_is_empty_get_can() {
	return (smaccm_queue_front_get_can == smaccm_queue_back_get_can) && (!smaccm_queue_full_get_can); 
}

bool smaccm_queue_read_get_can(SMACCM_DATA__Array_U8_80 get_can) {
	if (smaccm_queue_is_empty_get_can()) {
		return false;
	} else {
		memcpy(get_can, smaccm_queue_get_can[smaccm_queue_back_get_can], sizeof(SMACCM_DATA__Array_U8_80));

		smaccm_queue_back_get_can = (smaccm_queue_back_get_can + 1) % 1; 
		smaccm_queue_full_get_can = false ; 
		return true;
	}
}

bool smaccm_queue_write_get_can(const SMACCM_DATA__Array_U8_80 get_can) {
	if (smaccm_queue_is_full_get_can()) {
		return false;
	} else {
		memcpy(smaccm_queue_get_can[smaccm_queue_front_get_can], get_can, sizeof(SMACCM_DATA__Array_U8_80));

		smaccm_queue_front_get_can = (smaccm_queue_front_get_can + 1) % 1; 		
		if (smaccm_queue_back_get_can == smaccm_queue_front_get_can) { 
			smaccm_queue_full_get_can = true ; 
		}
		return true;
	}
}

/************************************************************************
 *  get_can_write_SMACCM_DATA__Array_U8_80: 
 * Invoked by: remote interface.
 * 
 * This is the function invoked by a remote RPC to write to an active-thread
 * input event data port.  It queues the input message into a circular buffer.
 * 
 ************************************************************************/

bool get_can_write_SMACCM_DATA__Array_U8_80(const smaccm_SMACCM_DATA__Array_U8_80_container * arg) {
	bool result;
	smaccm_server_get_can_mut_lock(); 
	result = smaccm_queue_write_get_can((uint8_t *) arg);
	smaccm_server_get_can_mut_unlock(); 
	return result;
}


/************************************************************************
 *  Server_read_get_can: 
 * Invoked from local active thread.
 * 
 * This is the function invoked by the active thread to read from the 
 * input event data queue circular buffer.
 * 
 ************************************************************************/

bool Server_read_get_can(SMACCM_DATA__Array_U8_80 arg) {
	bool result; 
	smaccm_server_get_can_mut_lock(); 
	result = smaccm_queue_read_get_can(arg);
	smaccm_server_get_can_mut_unlock(); 
	return result;
}



static SMACCM_DATA__Array_U8_80 * smaccm_tmp_array_send_output; 
static uint32_t * smaccm_tmp_used_send_output;
static uint32_t smaccm_max_tmp_array_send_output; 	
static SMACCM_DATA__Array_U8_80 * smaccm_tmp_array_send_can; 
static uint32_t * smaccm_tmp_used_send_can;
static uint32_t smaccm_max_tmp_array_send_can; 	


/************************************************************************
 * periodic_dispatcher Declarations
 * 
 ************************************************************************/

static bool smaccm_occurred_periodic_dispatcher;
static int64_t smaccm_time_periodic_dispatcher;

/************************************************************************
 * Server_periodic_dispatcher_write_int64_t
 * Invoked from remote periodic dispatch thread.
 * 
 * This function records the current time and triggers the active thread 
 * dispatch from a periodic event.
 * 
 ************************************************************************/

bool Server_periodic_dispatcher_write_int64_t(const int64_t * arg) {
	smaccm_occurred_periodic_dispatcher = true;
	smaccm_time_periodic_dispatcher = *arg;
	smaccm_dispatch_sem_post();

	return true;
}

 
 
 

/************************************************************************
 *  dispatch_dispatch_periodic_dispatcher: 
 * Invoked by remote RPC (or, for active thread, local dispatcher).
 * 
 * This is the function invoked by an active thread dispatcher to 
 * call to a user-defined entrypoint function.  It sets up the dispatch
 * context for the user-defined entrypoint, then calls it.
 * 
 ************************************************************************/

void dispatch_dispatch_periodic_dispatcher(
  const int64_t * in_arg ,
  smaccm_Server_periodic_dispatcher_struct *out_arg) {
	smaccm_max_tmp_array_send_output = 0;
	smaccm_max_tmp_array_send_can = 0;

	component_entry( in_arg); 

}	


/************************************************************************
 *  dispatch_dispatch_Server_initializer: 
 * Invoked by remote RPC (or, for active thread, local dispatcher).
 * 
 * This is the function invoked by an active thread dispatcher to 
 * call to a user-defined entrypoint function.  It sets up the dispatch
 * context for the user-defined entrypoint, then calls it.
 * 
 ************************************************************************/

void dispatch_dispatch_Server_initializer(
  const int64_t * in_arg ,
  smaccm_Server_Server_initializer_struct *out_arg) {
	smaccm_max_tmp_array_send_output = 0;
	smaccm_max_tmp_array_send_can = 0;

	component_init( in_arg); 

}	


/************************************************************************
 *  dispatch_dispatch_get_input: 
 * Invoked by remote RPC (or, for active thread, local dispatcher).
 * 
 * This is the function invoked by an active thread dispatcher to 
 * call to a user-defined entrypoint function.  It sets up the dispatch
 * context for the user-defined entrypoint, then calls it.
 * 
 ************************************************************************/

void dispatch_dispatch_get_input(
  const smaccm_SMACCM_DATA__Array_U8_80_container * in_arg ,
  smaccm_Server_get_input_struct *out_arg) {
	smaccm_max_tmp_array_send_output = 0;
	smaccm_max_tmp_array_send_can = 0;

}	


/************************************************************************
 *  dispatch_dispatch_get_can: 
 * Invoked by remote RPC (or, for active thread, local dispatcher).
 * 
 * This is the function invoked by an active thread dispatcher to 
 * call to a user-defined entrypoint function.  It sets up the dispatch
 * context for the user-defined entrypoint, then calls it.
 * 
 ************************************************************************/

void dispatch_dispatch_get_can(
  const smaccm_SMACCM_DATA__Array_U8_80_container * in_arg ,
  smaccm_Server_get_can_struct *out_arg) {
	smaccm_max_tmp_array_send_output = 0;
	smaccm_max_tmp_array_send_can = 0;

}	



/************************************************************************
 * Server_write_send_output 
 * Invoked from local active or passive thread.
 * 
 * This is the comm function invoked by a user-level thread to send a message 
 * to another thread.  It enqueues the request to be sent when the user thread
 * completes execution.
 * 
 ************************************************************************/

bool Server_write_send_output(const SMACCM_DATA__Array_U8_80 send_output) {
	if (smaccm_max_tmp_array_send_output > 0 && 
		 *smaccm_tmp_used_send_output < smaccm_max_tmp_array_send_output) {
		memcpy(smaccm_tmp_array_send_output[*smaccm_tmp_used_send_output], send_output, sizeof(SMACCM_DATA__Array_U8_80));

		(*smaccm_tmp_used_send_output)++;
		return true;
	} else {
		return false;
	}
}

/************************************************************************
 * Server_write_send_can 
 * Invoked from local active or passive thread.
 * 
 * This is the comm function invoked by a user-level thread to send a message 
 * to another thread.  It enqueues the request to be sent when the user thread
 * completes execution.
 * 
 ************************************************************************/

bool Server_write_send_can(const SMACCM_DATA__Array_U8_80 send_can) {
	if (smaccm_max_tmp_array_send_can > 0 && 
		 *smaccm_tmp_used_send_can < smaccm_max_tmp_array_send_can) {
		memcpy(smaccm_tmp_array_send_can[*smaccm_tmp_used_send_can], send_can, sizeof(SMACCM_DATA__Array_U8_80));

		(*smaccm_tmp_used_send_can)++;
		return true;
	} else {
		return false;
	}
}

SMACCM_DATA__camera_data_i smaccm_camera_data_var ;

/************************************************************************
 *  Server_read_camera_data: 
 * Invoked from local active thread.
 * 
 * This is the function invoked by the active thread to read from a data port.
 * 
 ************************************************************************/

bool Server_read_camera_data(SMACCM_DATA__camera_data_i * camera_data) {
	smaccm_server_camera_data_mut_lock(); 
	memcpy(camera_data, &smaccm_camera_data_var, sizeof(SMACCM_DATA__camera_data_i));
	smaccm_server_camera_data_mut_unlock(); 
	return true;
}

/************************************************************************
 *  camera_data_write_SMACCM_DATA__camera_data_i: 
 * Invoked by remote RPC.
 * 
 * This is the function that is invoked by an RPC to write to a data port.
 * 
 ************************************************************************/

bool camera_data_write_SMACCM_DATA__camera_data_i(const SMACCM_DATA__camera_data_i * camera_data) {
	smaccm_server_camera_data_mut_lock(); 
	memcpy(&smaccm_camera_data_var, camera_data, sizeof(SMACCM_DATA__camera_data_i));
	smaccm_server_camera_data_mut_unlock(); 
	return true;
}


/************************************************************************
 * 
smaccm_Server_periodic_dispatcher_dispatcher
 * Invoked from local active thread.
 * 
 * This is the dispatcher function invoked to respond to an incoming thread 
 * stimulus: an ISR, a periodic dispatch, or a queued event.
 * 
 ******************************************************************************/
static smaccm_Server_periodic_dispatcher_struct smaccm_Server_periodic_dispatcher_arg;

void 
smaccm_Server_periodic_dispatcher_dispatcher(int64_t * periodic_dispatcher) {

	 
	// make the call: 
	dispatch_dispatch_periodic_dispatcher( periodic_dispatcher,
  &smaccm_Server_periodic_dispatcher_arg	
		); 
	 

}
/************************************************************************
 * 
smaccm_Server_Server_initializer_dispatcher
 * Invoked from local active thread.
 * 
 * This is the dispatcher function invoked to respond to an incoming thread 
 * stimulus: an ISR, a periodic dispatch, or a queued event.
 * 
 ******************************************************************************/
static smaccm_Server_Server_initializer_struct smaccm_Server_Server_initializer_arg;

void 
smaccm_Server_Server_initializer_dispatcher(int64_t * Server_initializer) {

	 
	// make the call: 
	dispatch_dispatch_Server_initializer( Server_initializer,
  &smaccm_Server_Server_initializer_arg	
		); 
	 

}
/************************************************************************
 * 
smaccm_Server_get_input_dispatcher
 * Invoked from local active thread.
 * 
 * This is the dispatcher function invoked to respond to an incoming thread 
 * stimulus: an ISR, a periodic dispatch, or a queued event.
 * 
 ******************************************************************************/
static smaccm_Server_get_input_struct smaccm_Server_get_input_arg;

void 
smaccm_Server_get_input_dispatcher(SMACCM_DATA__Array_U8_80 get_input) {

	 
	// make the call: 
	dispatch_dispatch_get_input((smaccm_SMACCM_DATA__Array_U8_80_container *) get_input,
  &smaccm_Server_get_input_arg	
		); 
	 

}
/************************************************************************
 * 
smaccm_Server_get_can_dispatcher
 * Invoked from local active thread.
 * 
 * This is the dispatcher function invoked to respond to an incoming thread 
 * stimulus: an ISR, a periodic dispatch, or a queued event.
 * 
 ******************************************************************************/
static smaccm_Server_get_can_struct smaccm_Server_get_can_arg;

void 
smaccm_Server_get_can_dispatcher(SMACCM_DATA__Array_U8_80 get_can) {

	 
	// make the call: 
	dispatch_dispatch_get_can((smaccm_SMACCM_DATA__Array_U8_80_container *) get_can,
  &smaccm_Server_get_can_arg	
		); 
	 

}

 
/************************************************************************
 * run
 * Main active thread function.
 * 
 ************************************************************************/

int run() {
	// port initialization routines (if any)... 

	// thread initialization routines (if any)...
	  int64_t dummy_time = 0;

	  smaccm_Server_Server_initializer_dispatcher(&dummy_time);
	// register interrupt handlers (if any)...
	    

	// initial lock to await dispatch input.
	smaccm_dispatch_sem_wait();

	for(;;) {
		smaccm_dispatch_sem_wait();


		// drain the queues 
		if (smaccm_occurred_periodic_dispatcher) {
			smaccm_occurred_periodic_dispatcher = false;

			smaccm_Server_periodic_dispatcher_dispatcher(&smaccm_time_periodic_dispatcher);
		}

		while (!smaccm_queue_is_empty_get_input()) {
			SMACCM_DATA__Array_U8_80 get_input ;
			smaccm_queue_read_get_input(get_input);

			smaccm_Server_get_input_dispatcher(get_input); 
		}

		while (!smaccm_queue_is_empty_get_can()) {
			SMACCM_DATA__Array_U8_80 get_can ;
			smaccm_queue_read_get_can(get_can);

			smaccm_Server_get_can_dispatcher(get_can); 
		}


	}
	// won't ever get here, but form must be followed
	return 0;
}




/**************************************************************************
  End of autogenerated file: /home/john/git/smaccm/models/SmaccmPhaseIIIV2/components/Server/src/smaccm_Server.c
 **************************************************************************/
