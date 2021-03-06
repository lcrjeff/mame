// license:BSD-3-Clause
// copyright-holders:Nigel Barnes
/**********************************************************************

        BBC Micro Floppy Disc Controller slot emulation

**********************************************************************/

#pragma once

#ifndef __BBC_FDC_SLOT__
#define __BBC_FDC_SLOT__

#include "emu.h"


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_BBC_FDC_SLOT_ADD(_tag, _slot_intf, _def_slot, _fixed) \
	MCFG_DEVICE_ADD(_tag, BBC_FDC_SLOT, 0) \
	MCFG_DEVICE_SLOT_INTERFACE(_slot_intf, _def_slot, _fixed)

#define MCFG_BBC_FDC_SLOT_INTRQ_HANDLER(_devcb) \
	devcb = &bbc_fdc_slot_device::set_intrq_handler(*device, DEVCB_##_devcb);

#define MCFG_BBC_FDC_SLOT_DRQ_HANDLER(_devcb) \
	devcb = &bbc_fdc_slot_device::set_drq_handler(*device, DEVCB_##_devcb);


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> bbc_fdc_slot_device

class device_bbc_fdc_interface;

class bbc_fdc_slot_device : public device_t, public device_slot_interface
{
public:
	// construction/destruction
	bbc_fdc_slot_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	virtual ~bbc_fdc_slot_device();

	// callbacks
	template<class _Object> static devcb_base &set_intrq_handler(device_t &device, _Object object)
		{ return downcast<bbc_fdc_slot_device &>(device).m_intrq_handler.set_callback(object); }
	template<class _Object> static devcb_base &set_drq_handler(device_t &device, _Object object)
		{ return downcast<bbc_fdc_slot_device &>(device).m_drq_handler.set_callback(object); }

	DECLARE_WRITE_LINE_MEMBER( intrq_w ) { m_intrq_handler(state); }
	DECLARE_WRITE_LINE_MEMBER( drq_w) { m_drq_handler(state); }

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	device_bbc_fdc_interface *m_card;

private:
	devcb_write_line m_intrq_handler;
	devcb_write_line m_drq_handler;
};


// ======================> device_bbc_fdc_interface

class device_bbc_fdc_interface : public device_slot_card_interface
{
public:
	// construction/destruction
	device_bbc_fdc_interface(const machine_config &mconfig, device_t &device);
	virtual ~device_bbc_fdc_interface();

protected:
	bbc_fdc_slot_device *m_slot;
};


// device type definition
extern const device_type BBC_FDC_SLOT;

SLOT_INTERFACE_EXTERN( bbc_fdc_devices );


#endif
