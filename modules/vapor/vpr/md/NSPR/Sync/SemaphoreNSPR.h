/****************** <VPR heading BEGIN do not edit this line> *****************
 *
 * VR Juggler Portable Runtime
 *
 * Original Authors:
 *   Allen Bierbaum, Patrick Hartling, Kevin Meinert, Carolina Cruz-Neira
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile$
 * Date modified: $Date$
 * Version:       $Revision$
 * -----------------------------------------------------------------
 *
 ****************** <VPR heading END do not edit this line> ******************/

/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * VR Juggler is (C) Copyright 1998-2003 by Iowa State University
 *
 * Original Authors:
 *   Allen Bierbaum, Christopher Just,
 *   Patrick Hartling, Kevin Meinert,
 *   Carolina Cruz-Neira, Albert Baker
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/

#ifndef _VPR_SEMAPHORE_NSPR_H_
#define _VPR_SEMAPHORE_NSPR_H_

#include <vpr/vprConfig.h>

#include <stdio.h>
#include <pratom.h>

#include <vpr/Sync/CondVar.h>


namespace vpr
{

/**
 * Wrapper for semaphores implemented using condition variables.
 */
class VPR_CLASS_API SemaphoreNSPR
{
public:
   /**
    * Custructor.
    *
    * @pre None.
    * @post The semaphore variable for the class is initilized as an
    *       unnamed semaphore.
    *
    * @param initialValue The initial number of resources controlled by the
    *                     semaphore.  If not specified, the default value is 1.
    */
   SemaphoreNSPR(int initial_value = 1)
   {
      mCondVar = new CondVar;
      PR_AtomicSet(&mValue, initial_value);
   }

   /**
    * Destructor.
    *
    * @pre None.
    * @post The resources used by the semaphore variable are freed.
    */
   ~SemaphoreNSPR()
   {
      delete mCondVar;
   }

   /**
    * Locks this semaphore.
    *
    * @pre None.
    * @post The calling thread either acquires the semaphore until release()
    *       is called, or the caller is put at the tail of a wait and is
    *       suspended until such time as it can be freed and allowed to acquire
    *       the semaphore itself.
    *
    * @return vpr::ReturnStatus::Succeed is returned if a resource lock is
    *         acquired.  vpr::ReturnStatus::Fail is returned otherwise.
    */
   vpr::ReturnStatus acquire()
   {
      mCondVar->acquire();
      PR_AtomicDecrement(&mValue);

      while ( mValue < 0 )
      {
         mCondVar->wait();
      }
      mCondVar->release();

      return vpr::ReturnStatus();
   }

   /**
    * Acquires a read lock on a resource protected by this semaphore.
    *
    * @pre None.
    * @post The calling thread either acquires the semaphore until release()
    *       is called, or the caller is put at the tail of a wait and is
    *       suspended until such time as it can be freed and allowed to acquire
    *       the semaphore itself.
    *
    * @return vpr::ReturnStatus::Succeed is returned if a resource read lock is
    *         acquired.  vpr::ReturnStatus::Fail is returned otherwise.
    *
    * @note There is no special read semaphore for now.
    */
   vpr::ReturnStatus acquireRead()
   {
      return this->acquire();
   }

   /**
    * Acquires a write lock on a resource protected by this semaphore.
    *
    * @pre None.
    * @post The calling thread either acquires the semaphore until release()
    *       is called, or the caller is put at the tail of a wait and is
    *       suspended until such time as it can be freed and allowed to acquire
    *       the semaphore itself.
    *
    * @return vpr::ReturnStatus::Succeed is returned if a resource write lock
    *         is acquired.  vpr::ReturnStatus::Fail is returned otherwise.
    *
    * @note There is no special write semaphore for now.
    */
   vpr::ReturnStatus acquireWrite()
   {
      return this->acquire();
   }

   /**
    * Tries to acquire the a resource lock immediately (does not block).
    *
    * @pre None.
    * @post If the semaphore could be acquired by the caller, the caller
    *       gets control of the semaphore.  If the semaphore was already
    *       locked, the routine returns immediately without suspending the
    *       calling thread.
    *
    * @return vpr::ReturnStatus::Succeed is returned if a lock is acquired.
    *         vpr::ReturnStatus::Fail is returned if no resource could be
    *         locked without blocking.
    */
   vpr::ReturnStatus tryAcquire()
   {
      vpr::ReturnStatus status(vpr::ReturnStatus::Fail);

      if ( mValue >= 0 )
      {
         status = this->acquire();
      }

      return status;
   }

   /**
    * Tries to acquire a read lock on a resource (does not block).
    *
    * @pre None.
    * @post If the semaphore could be acquired by the caller, the caller
    *       gets control of the semaphore.  If the semaphore was already
    *       locked, the routine returns immediately without suspending the
    *       calling thread.
    *
    * @return vpr::ReturnStatus::Succeed is returned if a read lock is
    *         acquired.  vpr::ReturnStatus::Fail is returned if no resource
    *         could be locked without blocking.
    */
   vpr::ReturnStatus tryAcquireRead()
   {
      return this->tryAcquire();
   }

   /**
    * Tries to acquire a write lock on a resource (does not block).
    *
    * @pre None.
    * @post If the semaphore could be acquired by the caller, the caller
    *       gets control of the semaphore.  If the semaphore was already
    *       locked, the routine returns immediately without suspending the
    *       calling thread.
    *
    * @return vpr::ReturnStatus::Succeed is returned if a write lock is
    *         acquired.  vpr::ReturnStatus::Fail is returned if no resource
    *         could be locked without blocking.
    */
   vpr::ReturnStatus tryAcquireWrite()
   {
      return this->tryAcquire();
   }

   /**
    * Releases a resource lock.
    *
    * @pre The semaphore should have been locked before being released.
    * @post The semaphore is released and the thread at the head of the
    *       wait queue is allowed to execute again.
    *
    * @return vpr::ReturnStatus::Succeed is returned if a resource is
    *         unlocked successfully.  vpr::ReturnStatus::Fail is returned
    *         otherwise.
    */
   vpr::ReturnStatus release()
   {
      vpr::ReturnStatus status;

      mCondVar->acquire();
      PR_AtomicIncrement(&mValue);
      status = mCondVar->signal();
      mCondVar->release();

      return status;
   }

   /**
    * Resets the resource count for this semaphore.
    *
    * @pre None.
    * @post This semaphore's count is set to the specified value.
    *
    * @param val - The value to which the semaphore is reset.
    *
    * @return vpr::ReturnStatus::Succeed is returned if the resource count is
    *         reset successfully.  vpr::ReturnStatus::Fail is returned
    *         otherwise.
    *
    * @note If processes are waiting on the semaphore, the results are
    *       undefined.
    */
   vpr::ReturnStatus reset(int val)
   {
      vpr::ReturnStatus status;

      mCondVar->acquire();
      PR_AtomicSet(&mValue, val);
      status = mCondVar->broadcast();
      mCondVar->release();

      return status;
   }

   /**
    * Dumps the semaphore debug stuff and current state.
    *
    * @pre None.
    * @post All important data and debugging information related to this
    *       semaphore is dumped to the specified file descriptor (or to
    *       stderr if none is given).
    *
    * @param dest    File descriptor to which the output will be written.
    *                It defaults to stderr if no descriptor is specified.
    * @param message Message printed out before the output is dumped.
    */
   void dump(FILE* dest = stderr,
             const char* message = "\n------ Semaphore Dump -----\n") const
   {
      fprintf(dest, "%s", message);
      fprintf(dest, "Current semaphore value: %d", mValue);
   }

protected:
   CondVar*  mCondVar;     /**< Semaphore simulator variable for the class */
   PRInt32   mValue;       /**< The resource count */

   // Prevent assignment and initialization.
   void operator= (const SemaphoreNSPR &)
   {
      /* Do nothing. */ ;
   }

   SemaphoreNSPR(const SemaphoreNSPR &)
   {
      /* Do nothing. */ ;
   }
};

} // End of vpr namespace


#endif  /* _VPR_SEMAPHORE_NSPR_H_ */
