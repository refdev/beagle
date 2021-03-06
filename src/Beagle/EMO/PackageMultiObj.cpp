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
 *  \file   beagle/src/PackageMultiObj.cpp
 *  \brief  Source code of class PackageMultiObj.
 *  \author Christian Gagne
 *  $Revision: 1.3 $
 *  $Date: 2007/08/09 21:39:53 $
 */

#include "Beagle/EMO.hpp"

using namespace Beagle;


/*!
 *  \brief Construct package with multi-objective optimization objects.
 */
EMO::PackageMultiObj::PackageMultiObj(void) :
		PackageAbstract("PackageMultiObj")
{ }


/*!
 *  \brief Configure system by adding necessary components into it.
 *  \param ioSystem System to configure.
 */
void EMO::PackageMultiObj::configure(System& ioSystem)
{
	Beagle_StackTraceBeginM();
	Factory& lFactory = ioSystem.getFactory();

	// Add available basic types to the factory
	lFactory.insertAllocator("Beagle::EMO::AlgoNSGA2", new AlgoNSGA2::Alloc);
	lFactory.insertAllocator("Beagle::EMO::FitnessMultiObj", new FitnessMultiObj::Alloc);
	lFactory.insertAllocator("Beagle::EMO::FitnessMultiObjMin", new FitnessMultiObjMin::Alloc);
	lFactory.insertAllocator("Beagle::EMO::NPGA2Op", new NPGA2Op::Alloc);
	lFactory.insertAllocator("Beagle::EMO::NSGA2Op", new NSGA2Op::Alloc);
	lFactory.insertAllocator("Beagle::EMO::PackageMultiObj", new PackageMultiObj::Alloc);
	lFactory.insertAllocator("Beagle::EMO::ParetoFrontCalculateOp", new ParetoFrontCalculateOp::Alloc);
	lFactory.insertAllocator("Beagle::EMO::ParetoFrontHOF", new ParetoFrontHOF::Alloc);
	lFactory.insertAllocator("Beagle::EMO::StatsCalcFitnessMultiObjOp", new StatsCalcFitnessMultiObjOp::Alloc);

	// Set aliases
	lFactory.aliasAllocator("Beagle::EMO::AlgoNSGA2", "AlgoNSGA2");
	lFactory.aliasAllocator("Beagle::EMO::FitnessMultiObj", "FitnessMultiObj");
	lFactory.aliasAllocator("Beagle::EMO::FitnessMultiObjMin", "FitnessMultiObjMin");
	lFactory.aliasAllocator("Beagle::EMO::NPGA2Op", "NPGA2Op");
	lFactory.aliasAllocator("Beagle::EMO::NSGA2Op", "NSGA2Op");
	lFactory.aliasAllocator("Beagle::EMO::PackageMultiObj", "PackageMultiObj");
	lFactory.aliasAllocator("Beagle::EMO::ParetoFrontCalculateOp", "ParetoFrontCalculateOp");
	lFactory.aliasAllocator("Beagle::EMO::ParetoFrontHOF", "ParetoFrontHOF");
	lFactory.aliasAllocator("Beagle::EMO::StatsCalcFitnessMultiObjOp", "StatsCalcFitnessMultiObjOp");

	// Set some basic concept-type associations in factory
	lFactory.setConcept("Algorithm", "AlgoNSGA2");
	lFactory.setConcept("Fitness", "FitnessMultiObj");
	lFactory.setConcept("HallOfFame", "ParetoFrontHOF");
	lFactory.setConcept("StatsCalculateOp", "StatsCalcFitnessMultiObjOp");
	lFactory.setConcept("SelectionOp", "NPGA2Op");

	Beagle_StackTraceEndM();
}


/*!
 *  \brief List packages which current package depends.
 *  \return Bag with the packages instanciation on which current package depends.
 *
 *  PackageMultiObj depends on PackageBase.
 */
PackageAbstract::Bag EMO::PackageMultiObj::listDependencies(void)
{
	Beagle_StackTraceBeginM();
	PackageAbstract::Bag lDependencies;
	lDependencies.push_back(new EC::Package());
	return lDependencies;
	Beagle_StackTraceEndM();
}
