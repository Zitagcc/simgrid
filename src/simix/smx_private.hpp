/* Copyright (c) 2007-2010, 2012-2015. The SimGrid Team.
 * All rights reserved.                                                     */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the license (GNU LGPL) which comes with this package. */

#ifndef SIMGRID_SIMIX_PRIVATE_HPP
#define SIMGRID_SIMIX_PRIVATE_HPP

#include <simgrid/simix.hpp>
#include "smx_private.h"

/**
 * \brief destroy a context
 * \param context the context to destroy
 * Argument must be stopped first -- runs in maestro context
 */
static XBT_INLINE void SIMIX_context_free(smx_context_t context)
{
  delete context;
}

/**
 * \brief stops the execution of a context
 * \param context to stop
 */
static XBT_INLINE void SIMIX_context_stop(smx_context_t context)
{
  context->stop();
}

/**
 \brief suspends a context and return the control back to the one which
        scheduled it
 \param context the context to be suspended (it must be the running one)
 */
static XBT_INLINE void SIMIX_context_suspend(smx_context_t context)
{
  context->suspend();
}

/**
 \brief Executes all the processes to run (in parallel if possible).
 */
static XBT_INLINE void SIMIX_context_runall(void)
{
  if (!xbt_dynar_is_empty(simix_global->process_to_run))
    simix_global->context_factory->run_all();
}

/**
 \brief returns the current running context
 */
static XBT_INLINE smx_context_t SIMIX_context_self(void)
{
  if (simix_global && simix_global->context_factory)
    return simix_global->context_factory->self();
  else
    return nullptr;
}

/**
 \brief returns the SIMIX process associated to a context
 \param context The context
 \return The SIMIX process
 */
static XBT_INLINE smx_process_t SIMIX_context_get_process(smx_context_t context)
{
  return context->process();
}

namespace simgrid {
namespace simix {

XBT_PRIVATE ContextFactory* thread_factory();
XBT_PRIVATE ContextFactory* sysv_factory();
XBT_PRIVATE ContextFactory* raw_factory();
XBT_PRIVATE ContextFactory* boost_factory();

}
}

#endif