/** @file */

#ifndef __VISUALIZE_DEBUG_IP_LAYOUT_HELPER__
#define __VISUALIZE_DEBUG_IP_LAYOUT_HELPER__

#include "xclbin.h"
#include "easylogging++.h"
#include <iostream>

/**
 * Helper for visualizing Debug IP Layout
 * 
 * This function takes a void pointer, then
 * cast it to Debug IP Layout, and print it
 * to console.
 */
void visualize_debug_ip_layout(void* data /**< [in] the memory that contains the Debug IP Layout data */) {
    LOG(INFO) << "Casting sysfs result to debug ip layout ...";
    debug_ip_layout* dbg = reinterpret_cast<debug_ip_layout*>(data);
    LOG(INFO) << "Type casting finished";
    LOG(INFO) << "Debug IP layout contains " << dbg->m_count << " entries";
    for (unsigned i = 0; i < dbg->m_count; ++i) {
        LOG(INFO) << "\t Showing debug_ip_layout[" << i << "]:";
        LOG(INFO) << "\t\t m_type: " << (unsigned)dbg->m_debug_ip_data[i].m_type;
        LOG(INFO) << "\t\t m_index: " << (unsigned)dbg->m_debug_ip_data[i].m_index;
        LOG(INFO) << "\t\t m_properties: 0x" << hex << (unsigned)dbg->m_debug_ip_data[i].m_properties << dec;
        LOG(INFO) << "\t\t m_major: " << (unsigned)dbg->m_debug_ip_data[i].m_major;
        LOG(INFO) << "\t\t m_minor: " << (unsigned)dbg->m_debug_ip_data[i].m_minor;
        LOG(INFO) << "\t\t m_base_address: 0x" << hex << (unsigned)dbg->m_debug_ip_data[i].m_base_address << dec;
        LOG(INFO) << "\t\t m_name: " << (char*)dbg->m_debug_ip_data[i].m_name;
    }
}

#endif