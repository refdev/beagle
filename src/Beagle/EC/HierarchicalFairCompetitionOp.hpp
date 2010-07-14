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
 *  \file   Beagle/EC/HierarchicalFairCompetitionOp.hpp
 *  \brief  Definition of the class Beagle::EC::HierarchicalFairCompetitionOp.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.11 $
 *  $Date: 2007/08/17 18:09:12 $
 */


#ifndef Beagle_EC_HierarchicalFairCompetitionOp_hpp
#define Beagle_EC_HierarchicalFairCompetitionOp_hpp

#include "Beagle/Core.hpp"


namespace Beagle
{
	
namespace EC
{

/*!
 *  \class HierarchicalFairCompetitionOp Beagle/EC/HierarchicalFairCompetitionOp.hpp "Beagle/EC/HierarchicalFairCompetitionOp.hpp"
 *  \brief Hierarchical fair competition replacement strategy operator class.
 *  \ingroup EC
 *  \ingroup Op
 *
 *  Hierachical Fair Competition (HCF) operator inspired by the work of Jianjun Hu
 *  and Erik Goodman (Michigan State University). The operator is actually
 *  implemented as a migration operator that is at the same time a replacement
 *  strategy. The breeder tree of the replacement strategy is called to
 *  generate the new individuals.
 *
 *  The operator acts on the population by migrating individuals from low-index
 *  to high-index demes. Individuals are migrating into the actual deme i from
 *  the migration buffer of deme i-1 (no migration in for deme 0). Then individuals
 *  better than the fitness threshold for deme i are moved into its migration buffer
 *  (no migration out for the last deme). If the deme is too small, new individuals
 *  are generated by the breeder tree to fill the deme. If the deme is too big, the
 *  worse individuals are erased from the deme.
 *
 *  An internal table of fitness threshold is kept internaly in the HFC operator.
 *  This fitness threshold is the value used to decide which individuals are migrated
 *  between deme. The HFC percentile value T (parameter 'ec.hfc.percentile') states
 *  to use fitness of the individual of deme i+1 at generation g-1 that is better than
 *  T percent of the individuals in the population as the fitness threshold for
 *  migrating individuals of deme i at generation g.
 *
 *  For an example of a XML configuration file with HFC operator, see file
 *  "symbreg-hfc.conf" in symbolic regression example.
 *
 *  References:
 *  Jianjun Hu and E. Goodman. Adaptive Hierarchical Fair Competition Model for
 *  Parallel Evolutionary Algorithms. Genetic and Evolutionary Computation
 *  Conference 2002, New York.
 *
 */
class HierarchicalFairCompetitionOp : public Beagle::ReplacementStrategyOp
{

public:

	//! HierarchicalFairCompetitionOp allocator type.
	typedef Beagle::AllocatorT<HierarchicalFairCompetitionOp,Beagle::ReplacementStrategyOp::Alloc>
	Alloc;
	//! HierarchicalFairCompetitionOp handle type.
	typedef Beagle::PointerT<HierarchicalFairCompetitionOp,Beagle::ReplacementStrategyOp::Handle>
	Handle;
	//! HierarchicalFairCompetitionOp bag type.
	typedef Beagle::ContainerT<HierarchicalFairCompetitionOp,Beagle::ReplacementStrategyOp::Bag>
	Bag;

	HierarchicalFairCompetitionOp(std::string inName="HierarchicalFairCompetitionOp");
	virtual ~HierarchicalFairCompetitionOp()
	{ }

	virtual void registerParams(Beagle::System& ioSystem);
	virtual void operate(Beagle::Deme& ioDeme, Beagle::Context& ioContext);

protected:

	Beagle::Individual::Bag generateIndividuals(unsigned int inN, Beagle::Deme& ioDeme, Beagle::Context& ioContext) const;

	Beagle::Fitness::Bag      mFitnessThresholds;  //!< Fitness thresholds used for migration.
	Beagle::Float::Handle     mHFCPercentile;      //!< HFC percentile used for to select fitness thresholds.
	Beagle::UInt::Handle      mMigrationInterval;  //!< Random ring migration interval (in generation).
	Beagle::UInt::Handle      mNumberMigrants;     //!< Number of migrants.
	Beagle::UIntArray::Handle mPopSize;            //!< Population size for the evolution.

};

}

}

#endif // Beagle_EC_HierarchicalFairCompetitionOp_hpp