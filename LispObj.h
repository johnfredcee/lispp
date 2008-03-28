
#ifndef H_LISP_OBJ
#define H_LISP_OBJ

namespace Lisp
{
	
	class LispObj;
    class LispNIL;
	class LispCons;
	class LispString;
	class LispFixnum;
	class LispFloat;
	class LispSymbol;
	class LispPackage;
	class LispFunc;
	
	class LispObj
	{
		public:			

			enum eLispObjectType
			{
				eBaseObj  = 0,
				eNullObj,                
				eStringObj,
                eConsObj,
				eFixnumObj,
				eFloatObj,
                eSymbolObj,
				ePackageObj,
				eFunctionObj                
			};

            /* api any lispobj must implement */
			virtual void getObjectType(eLispObjectType& kind) = 0;
			virtual LispObjRef create(void) = 0;
			virtual LispObjRef clone(void) const = 0;
			virtual void print(std::ostream& out) const = 0;
			virtual LispObjPtr read(std::istream& in) = 0;
            

		protected:
			LispObj() {};
			LispObj(const LispObj& other) {};
			LispObj& operator=(const LispObj& other) {};
	};

	class LispEnv;

	class LispEnv {

        private:

			LispEnv *parent_;

            // to do -- this needs to be a hash table
            typedef std::pair<LispObj*,LispObj*> Binding;

			std::vector<Binding> env_;

            class IsBound
            {
                private:
                    LispObj* bound_;
                public:
                    IsBound(bound) :
                        bound_(bound)
                    {}
                    
                    bool operator()(const LispEnv::Binding& binding) {
                        return (*bound_ == *(binding.first));
                    }
            };

		public:

            
			LispEnv() :
				parent_(NULL)
			{
				assert(root_environment != NULL);
				root_environment = this;
			};

			LispEnv(LispEnv* parent) :
				parent_(parent)
			{}
		
			std::size_t add(LispObj* obj)
			{
				std::size_t result = env_.size();
				env_.push_back(obj);
				return result;
			}

            LispObj* binding(LispObj* bound)
            {
                std::vector<Binding>::iterator result;
                result = std::find_if(result.begin(), result.end(), IsBound(bound));
            }
            
			LispEnv *child(void)
			{
				current_environment = new LispEnv(this);
				return current_environment;
			}

			virtual ~LispEnv()
			{
				assert(this == LispEnv::current_environment);
                LispEnv::current_environment = parent_;
			}
		
			static LispEnv *root_environment;
			static LispEnv *current_environment;

	};	
	
}


#endif


