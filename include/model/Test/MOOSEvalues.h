/* This file is part of MODEL, the Mechanics Of Defect Evolution Library.
 *
 * Copyright (C) 2011 by Giacomo Po <gpo@ucla.edu>.
 *
 * model is distributed without any warranty under the
 * GNU General Public License (GPL) v2 <http://www.gnu.org/licenses/>.
 */

#ifndef model_MOOSEvalue_H_
#define model_MOOSEvalue_H_

namespace model
{
    
    template <int dim>
    class MOOSEvalues
    {
              
    public:
	typedef Eigen::Matrix<double, dim, dim> StressMatrixType;
	typedef Eigen::Matrix<double, dim, 1> pointVectorType;
        /*
        typedef Eigen::SparseMatrix<double> SparseMatrixType;
        
        const SimplicialMesh<dim>& mesh;
        size_t gSize;
        */
        // static bool apply_DD_displacement;
        static bool use_MOOSE;

        void setDDobject(std::vector<System *> MOOSE_sys_sig, std::vector<MooseVariable *> MOOSE_var_sig);

    private:
	StressMatrixType MOOSEstress;	// matrix of stress tensor
	std::vector<System *> _sys_sig;
	std::vector<MooseVariable *> _var_sig;
	/*
        Eigen::Matrix<double,6,6> C; // matrix of elastic moduli
        FiniteElementType* fe;
        TrialFunctionType*  u;  // displacement field *u=[u1 u2 u3]'
        TrialGradType*  b;      // displacement gradient *b=[u11 u12 u13 u21 u22 u23 u31 u32 u33]'
        TrialDefType*  e;       // strain *e=[e11 e22 e33 e12 e23 e13]'
        TrialStressType* s;     // stress *s=[s11 s22 s33 s12 s23 s13]'
        
        IntegrationDomainType dV;
        BilinearWeakFormType* bWF;
        
        LoadControllerType* lc;
        
        SparseMatrixType A;
        SparseMatrixType T;
        SparseMatrixType A1;
        */
        /**********************************************************************/
	
        //Eigen::Matrix<double,6,6> get_C(const double& mu, const double& nu) const
        //{
        //    const double lam=2.0*mu*nu/(1.0-2.0*nu);
        //    const double C11(lam+2.0*mu);
        //    const double C12(lam);
        //    const double C44(mu); // C multiplies engineering strain
            
        //    Eigen::Matrix<double,6,6> temp;
        //    temp<<C11, C12, C12, 0.0, 0.0, 0.0,
        //    /***/ C12, C11, C12, 0.0, 0.0, 0.0,
        //    /***/ C12, C12, C11, 0.0, 0.0, 0.0,
        //    /***/ 0.0, 0.0, 0.0, C44, 0.0, 0.0,
        //    /***/ 0.0, 0.0, 0.0, 0.0, C44, 0.0,
        //    /***/ 0.0, 0.0, 0.0, 0.0, 0.0, C44;
        //    return temp;
        //}
  
        
    public:
        
        //double tolerance;
        
        /**********************************************************************/
        //BVPsolver(const SimplicialMesh<dim>& mesh_in) :
	
        ///* init  */ mesh(mesh_in),
        ///* init  */ gSize(0),
        ///* init  */ C(get_C(1.0,0.33)),
        ///* init  */ tolerance(0.0001)
        //{
            
        //}
        
        /**********************************************************************/
	/*
        const FiniteElementType& finiteElement() const
        {
            return *fe;
        }
        */
        
        /**********************************************************************/
	
        //template <typename DislocationNetworkType>
        //void init(const DislocationNetworkType& DN)
        //{
        //    std::cout<<"Initializing BVPsolver"<<std::endl;
	    /*
            fe = new FiniteElementType(mesh);
            u  = new TrialFunctionType(fe->template trial<'u',dim>());
            b  = new TrialGradType(grad(*u));
            e  = new TrialDefType(def(*u));
            C=get_C(DN.poly.mu,DN.poly.nu); // Material<Isotropic>  may have changed since construction
            s  = new TrialStressType(C**e);
            dV = fe->template domain<EntireDomain,4,GaussLegendre>();
            bWF = new BilinearWeakFormType((test(*e),*s),dV);
            gSize=TrialBase<TrialFunctionType>::gSize();
            
            // Compute and store stiffness matrix
            const auto t0= std::chrono::system_clock::now();
            std::cout<<"Computing stiffness matrix: gSize="<<gSize<<std::endl;
            std::vector<Eigen::Triplet<double> > globalTriplets(bWF->globalTriplets());
            A.resize(gSize,gSize);
            A.setFromTriplets(globalTriplets.begin(),globalTriplets.end());
            A.prune(A.norm()/A.nonZeros(),FLT_EPSILON);
            model::cout<<" ["<<(std::chrono::duration<double>(std::chrono::system_clock::now()-t0)).count()<<" sec]"<<std::endl;
        
            // Initialize LoadController
            lc = new LoadControllerType(displacement());
            lc ->init(DN);
        }
        */
        

        /**********************************************************************/
	
        StressMatrixType stress(const Point P) const
        {
            StressMatrixType tempS;
	    for (int i = 0; i < dim; i++)
	    {
		for (int j = 0; j < dim; j++)
		{
		    	tempS(i, j) = _sys_sig[i * dim + j]->point_value(_var_sig[i * dim + j]->number(), P, false)/161.0e9;
		    	//std::cout << tempS(i, j) << ", ";
		}
		//std::cout << std::endl;
	    }    
            return tempS;
        }        
	
    };
    
    
    template <int dim>
    bool MOOSEvalues<dim>::use_MOOSE=true;
    
    template <int dim>	
    void MOOSEvalues<dim>::setDDobject(std::vector<System *> MOOSE_sys_sig, std::vector<MooseVariable *> MOOSE_var_sig)
    {
	_sys_sig = MOOSE_sys_sig;
	_var_sig = MOOSE_var_sig;
    }
    
} // namespace model
#endif

