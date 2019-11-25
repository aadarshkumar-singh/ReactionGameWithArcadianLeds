/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2014  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation,
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/*
 * Author: 2000-2004 Paolo Gai
 *         2009 Bernardo Dal Seno
 */

/*
 * PSoC Port and API Generation
 * Carlos Fernando Meier Martinez
 * Hochschule Darmstadt, Germany. 2017.
 */

#ifndef PKG_EE_H
#define PKG_EE_H

#include "OS_ReactionGame_eecfg.inc"

#include "OS_ReactionGame_ee_rtdruid_versions.inc"

#if defined(__cplusplus)
extern "C" {
#endif

  /*
   *
   * CPU
   *
   */

#ifdef __CORTEX_MX__
#include "OS_ReactionGame_cortex_mx_ee_cpu.inc"
#endif

  /*
   *
   * MCU
   *
   */

  /*
   *
   * Kernel
   *
   */

/* OO */
#if (defined(__OO_BCC1__)) || (defined(__OO_BCC2__))    \
  || (defined(__OO_ECC1__)) || (defined(__OO_ECC2__)) || (defined(__AS_SC4__))
#include "OS_ReactionGame_ee_oo_kernel.inc"
#include "OS_ReactionGame_ee_as_kernel.inc"
/* Moved inline interrupt services inclusion here, because they need to see TP
   declarations */
#include "OS_ReactionGame_ee_oo_inline.inc"
#ifdef EE_AS_IOC__
#include "OS_ReactionGame_ee_as_ioc.inc"
/*                                 WARNING
   The following file SHALL be generated by IOC Generator: if you are using
   Erika IOC implementation without a generator you MUST provide it in your
   project root. */
#include "OS_ReactionGame_ioc_common.inc"
#endif /* EE_AS_IOC__ */

#ifdef EE_AS_SCHEDULETABLES__
#include "OS_ReactionGame_ee_as_schedule_tables.inc"
#endif /* EE_AS_SCHEDULETABLES__ */

#endif /* OO */

/* SEM */
#ifdef __SEM__
#include "OS_ReactionGame_ee_sem.inc"
#endif

/* ALARMS */
#ifdef __ALARMS__
#include "OS_ReactionGame_ee_alarms.inc"
#endif

/* RN */
#if (defined(__RN__)) || (defined(EE_AS_RPC__))
#include "OS_ReactionGame_ee_rn.inc"
#endif /* __RN__ || EE_AS_RPC__ */

  /*
   *
   * API
   *
   */

#include "OS_ReactionGame_ee_api.inc"

  /*
   *
   * IRQ
   *
   */

#include "OS_ReactionGame_ee_irq.inc"

/* Assert inclusion if enabled */
#ifdef __ASSERT__
#include "OS_ReactionGame_ee_assert.inc"
#endif /* __ASSERT__ */

#if defined(__cplusplus)
};
#endif

#endif /* __INCLUDE_PKG_EE_H__ */

/* [] END OF FILE */
