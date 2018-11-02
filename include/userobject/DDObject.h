#ifndef DDOBJECT_H
#define DDOBJECT_H

#include "GeneralUserObject.h"
//#include "LoopNetworkTest.h"
#include "DislocationNetwork.h"

//Forward Declarations
class DDObject;

template<>
InputParameters validParams<DDObject>();

class DDObject : public GeneralUserObject
{
public:
	DDObject(const InputParameters & parameters);	

 	virtual void initialSetup();	// Only run once at the beginning of simulation
	virtual void residualSetup() {}
	virtual void timestepSetup() {}

	virtual void initialize();	// Called before execute() is ever called so that data can be cleared.
	virtual void execute();		// Execute method.
	virtual void finalize(){}	// Finalize.  This is called _after_ execute() and _after_ threadJoin()!  This is probably where you want to do MPI communication!

	static const unsigned int _dim = 3; 

    /**
  	* Optional interface function for "evaluating" a UserObject at a spatial position.
 	* If a UserObject overrides this function that UserObject can then be used in a
 	* Transfer to transfer information from one domain to another.
 	*/
 	//virtual Real spatialValue(const Point & p) const;
    Eigen::Matrix<double, 3, 3> spatialValues(const Eigen::Matrix<double, 3, 1> & p);
	
	const Real PI = std::acos(-1);

    /* argc & argv*/
    int argc = 1;
    char a = '.';
    char b = '-';
    char c = 'D'; 
    std::vector<char *> argVec = {&a};
    char ** argv = &argVec[0];

    // Create the loops
    std::vector<size_t> loop0;
    // Returns a reference to the network
    // model::Dnetwork & getNetwork(){return DN;}

    std::vector<Point> getLoopNodes() const {return loopNodes;}

    std::vector<Number> getNodalClimbVelocity() const {return nodalClimbVelocity;}

protected:
    // Create the DislocationNetwork
    #define ExternalLoadControllerFile "UniformExternalLoadController.h"
    model::DislocationNetwork<3,0,model::Hermite> _DN;
    // Pointer to the EquationSystem object
    System * _sys;
    // Pointer to the MooseVariable
    MooseVariable * _var_c;
    // Vector of variable names
    std::vector<VariableName> _stressCompName;
    // Vector of nodes in one loop
    std::vector<Point> loopNodes;
    // Vector of velocity magnitude on nodes
    std::vector<Number> nodalClimbVelocity;

    // Constants
    Real _diffusivity;
    Real _Uvd;
    Real _Uvf; //[eV], vacancy formation energy
    const Real _kB;
    const Real _eV2J;
    const Real _Omega;
    Real _T;
    Real _Dv;
    const Real _burgers;
    Real _c0; // equilibrium concentation in defect-free crystal
};


#endif // DDOBJECT_H
