#pragma once
#include "i_handle_entity.hpp"
#define num_ent_entry_bits         (11 + 2)
#define num_ent_entries            (1 << num_ent_entry_bits)
#define invalid_ehandle_index 0xffffffff
#define num_serial_num_bits        16 // (32 - num_ent_entry_bits)
#define num_serial_num_shift_bits (32 - num_serial_num_bits)
#define ent_entry_mask             (( 1 << num_serial_num_bits) - 1)

class c_base_handle
{
	friend class c_base_entity_list;
public:
	c_base_handle( );
	c_base_handle( const c_base_handle& other );
	c_base_handle( unsigned long value );
	c_base_handle( int iEntry, int iSerialNumber );

	void init( int iEntry, int iSerialNumber );
	void term( );

	// Even if this returns true, Get() still can return return a non-null value.
	// This just tells if the handle has been initted with any values.
	bool is_valid( ) const;

	int get_entry_index( ) const;
	int get_serial_number( ) const;

	int to_int( ) const;
	bool operator !=( const c_base_handle& other ) const;
	bool operator ==( const c_base_handle& other ) const;
	bool operator ==( const i_handle_entity* pEnt ) const;
	bool operator !=( const i_handle_entity* pEnt ) const;
	bool operator <( const c_base_handle& other ) const;
	bool operator <( const i_handle_entity* pEnt ) const;

	// Assign a value to the handle.
	const c_base_handle& operator=( const i_handle_entity* pEntity );
	const c_base_handle& set( const i_handle_entity* pEntity );

	i_handle_entity* get( ) const;
protected:
	unsigned long  m_Index;
};

inline c_base_handle::c_base_handle( )
{
	m_Index = invalid_ehandle_index;
}

inline c_base_handle::c_base_handle( const c_base_handle& other )
{
	m_Index = other.m_Index;
}

inline c_base_handle::c_base_handle( unsigned long value )
{
	m_Index = value;
}

inline c_base_handle::c_base_handle( int iEntry, int iSerialNumber )
{
	init( iEntry, iSerialNumber );
}

inline void c_base_handle::init( int iEntry, int iSerialNumber )
{
	m_Index = ( unsigned long ) ( iEntry | ( iSerialNumber << num_serial_num_shift_bits ) );
}

inline void c_base_handle::term( )
{
	m_Index = invalid_ehandle_index;
}

inline bool c_base_handle::is_valid( ) const
{
	return m_Index != invalid_ehandle_index;
}

inline int c_base_handle::get_entry_index( ) const
{
	// There is a hack here: due to a bug in the original implementation of the 
	// entity handle system, an attempt to look up an invalid entity index in 
	// certain cirumstances might fall through to the the mask operation below.
	// This would mask an invalid index to be in fact a lookup of entity number
	// NUM_ENT_ENTRIES, so invalid ent indexes end up actually looking up the
	// last slot in the entities array. Since this slot is always empty, the 
	// lookup returns NULL and the expected behavior occurs through this unexpected
	// route.
	// A lot of code actually depends on this behavior, and the bug was only exposed
	// after a change to NUM_SERIAL_NUM_BITS increased the number of allowable
	// static props in the world. So the if-stanza below detects this case and 
	// retains the prior (bug-submarining) behavior.
	if ( !is_valid( ) )
		return num_ent_entries - 1;
	return m_Index & ent_entry_mask;
}

inline int c_base_handle::get_serial_number( ) const
{
	return m_Index >> num_serial_num_shift_bits;
}

inline int c_base_handle::to_int( ) const
{
	return ( int ) m_Index;
}

inline bool c_base_handle::operator !=( const c_base_handle& other ) const
{
	return m_Index != other.m_Index;
}

inline bool c_base_handle::operator ==( const c_base_handle& other ) const
{
	return m_Index == other.m_Index;
}

inline bool c_base_handle::operator ==( const i_handle_entity* pEnt ) const
{
	return get( ) == pEnt;
}

inline bool c_base_handle::operator !=( const i_handle_entity* pEnt ) const
{
	return get( ) != pEnt;
}

inline bool c_base_handle::operator <( const c_base_handle& other ) const
{
	return m_Index < other.m_Index;
}

inline bool c_base_handle::operator <( const i_handle_entity* pEntity ) const
{
	unsigned long otherIndex = ( pEntity ) ? pEntity->get_ref_handle( ).m_Index : invalid_ehandle_index;
	return m_Index < otherIndex;
}

inline const c_base_handle& c_base_handle::operator=( const i_handle_entity* pEntity )
{
	return set( pEntity );
}

inline const c_base_handle& c_base_handle::set( const i_handle_entity* pEntity )
{
	if ( pEntity )
		*this = pEntity->get_ref_handle( );
	else
		m_Index = invalid_ehandle_index;

	return *this;
}
