/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include "timer_api.h"
#include "../drivers/timer/socfpga_timer.h"

timer_handle_t timer_open(timer_instance_t instance)
{
	return timer_ll_open(instance);
}

int32_t timer_start(timer_handle_t htimer)
{
	return timer_ll_start(htimer);
}

int32_t timer_stop(timer_handle_t htimer)
{
	return timer_ll_stop(htimer);
}

int32_t timer_close(timer_handle_t htimer)
{
	return timer_ll_close(htimer);
}

int32_t timer_deinit(timer_handle_t htimer)
{
	return timer_close(htimer);
}

int32_t timer_get_time_us(timer_handle_t htimer, uint32_t *time_us)
{
	return timer_get_value_us(htimer, time_us);
}