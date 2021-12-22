/*******************************************************************************
 ################################################################################
 #
 # This program is free software; you can redistribute it and/or modify it under
 # the terms of the GNU General Public License version 2 and only version 2 as
 # published by the Free Software Foundation.
 #
 # This program is distributed in the hope that it will be useful, but WITHOUT
 # ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 # FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 # details.
 #
 # You should have received a copy of the GNU General Public License along with
 # this program; if not, write to the Free Software Foundation, Inc.,
 # 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 #
 #------------------------------------------------------------------------------
 #                             Imaging Division
 ################################################################################
 ********************************************************************************/

/**
 * Proximity and ALS configuration
 */

#ifndef VL6180_CFG_H_
#define VL6180_CFG_H_

#define VL6180_UPSCALE_SUPPORT               -2

#define VL6180_ALS_SUPPORT                   1

#define VL6180_HAVE_DMAX_RANGING             1

#define VL6180_WRAP_AROUND_FILTER_SUPPORT    1

#define VL6180_EXTENDED_RANGE                0

#define VL6180_CACHED_REG                    1


#if (VL6180_EXTENDED_RANGE) && (VL6180_ALS_SUPPORT)
#warning "Als support should be OFF for extended range"
#endif

#endif

/* VL6180_CFG_H_ */
