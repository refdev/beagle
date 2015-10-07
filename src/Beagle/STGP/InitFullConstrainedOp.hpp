/*
 *  Open BEAGLE
 *  Copyright (C) 2001-2007 by Christian Gagne and Marc Parizeau
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Contact:
 *  Laboratoire de Vision et Systemes Numeriques
 *  Departement de genie electrique et de genie informatique
 *  Universite Laval, Quebec, Canada, G1K 7P4
 *  http://vision.gel.ulaval.ca
 *
 */

/*!
 *  \file   beagle/GP/InitFullConstrainedOp.hpp
 *  \brief  Definition of the class GP::InitFullConstrainedOp.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.13 $
 *  $Date: 2007/08/08 19:26:35 $
 */

#ifndef Beagle_GP_InitFullConstrainedOp_hpp
#define Beagle_GP_InitFullConstrainedOp_hpp

#include <string>

#include "Beagle/config.hpp"
#include "Beagle/macros.hpp"
#include "Beagle/Core/Object.hpp"
#include "Beagle/Core/AllocatorT.hpp"
#include "Beagle/Core/PointerT.hpp"
#include "Beagle/Core/ContainerT.hpp"
#include "Beagle/EC/InitializationOp.hpp"
#include "Beagle/Core/UInt.hpp"
#include "Beagle/Core/Bool.hpp"
#include "Beagle/GP/Tree.hpp"
#include "Beagle/GP/InitFullOp.hpp"


namespace Beagle
{
namespace STGP
{

/*!
 *  \class InitFullConstrainedOp
 *     beagle/GP/InitFullConstrainedOp.hpp "beagle/GP/InitFullConstrainedOp.hpp"
 *  \brief Constrained GP trees "full" initialization operator class.
 *  \ingroup GPF
 *  \ingroup GPOp
 *  \ingroup GPPop
 */
class InitFullConstrainedOp : public GP::InitFullOp
{

public:

	//! GP::InitFullConstrainedOp allocator type.
	typedef AllocatorT<InitFullConstrainedOp,GP::InitFullOp::Alloc>
	Alloc;
	//! GP::InitFullConstrainedOp handle type.
	typedef PointerT<InitFullConstrainedOp,GP::InitFullOp::Handle>
	Handle;
	//! GP::InitFullConstrainedOp bag type.
	typedef ContainerT<InitFullConstrainedOp,GP::InitFullOp::Bag>
	Bag;

	explicit InitFullConstrainedOp(std::string inReproProbaName="ec.repro.prob",
	                               std::string inName="GP-InitFullConstrainedOp");
	virtual ~InitFullConstrainedOp()
	{ }

	virtual void registerParams(Beagle::System& ioSystem);
	virtual unsigned int initTree(GP::Tree& outTree,
	                              unsigned int inMinDepth,
	                              unsigned int inMaxDepth,
	                              GP::Context& ioContext) const;

protected:

	unsigned int initConstrainedSubTreeFull(GP::Tree& ioTree,
	                                        unsigned int inSubTreeDepth,
	                                        GP::Context& ioContext) const;

	UInt::Handle mNumberAttempts;   //!< Number of attempts in each initialization.

};

}
}

#endif // Beagle_GP_InitFullConstrainedOp_hpp