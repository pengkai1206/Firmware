/****************************************************************************
 *
 *   Copyright (C) 2017 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file px4_shutdown.h
 * Power-related API
 */

#pragma once

#include <stdbool.h>

__BEGIN_DECLS

/**
 * Shutdown hook callback method (@see px4_register_shutdown_hook()).
 * @return true if it's ok to shutdown, false if more time needed for cleanup
 */
typedef bool (*shutdown_hook_t)(void);


/**
 * Register a method that should be called when powering off (and also on reboot).
 * @param hook callback method. It must not block, but return immediately.
 *        When the system is requested to shutdown, the registered hooks will be
 *        called regularily until either all of them return true, or a timeout
 *        is reached.
 * @return 0 on success, <0 on error
 */
__EXPORT int px4_register_shutdown_hook(shutdown_hook_t hook);


/**
 * Unregister a shutdown hook
 * @param hook callback method to be removed
 * @return 0 on success, <0 on error
 */
__EXPORT int px4_unregister_shutdown_hook(shutdown_hook_t hook);


/**
 * Request the system to shut down. It's save to call this from an IRQ context,
 * but the work queues need to be initialized already.
 * Note the following:
 * - The system might not support to shutdown (or reboot). In that case -EINVAL will
 *   be returned.
 * - The system might not shutdown immediately, so expect this method to return even
 *   on success.
 * @param reboot perform a reboot instead of a shutdown
 * @param to_bootloader reboot into bootloader mode (only used if reboot is true)
 * @return 0 on success, <0 on error
 */
__EXPORT int px4_shutdown_request(bool reboot, bool to_bootloader);

__END_DECLS

