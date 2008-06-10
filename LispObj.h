
#ifndef H_LISP_OBJ
#define H_LISP_OBJ

#include <cassert>
#include <ostream>
#include <vector>
#include <string>

namespace Lisp
{
	
    class Obj;
    class NIL;
    class Cons;
    class String;
    class Fixnum;
    class Floatnum;
    class Symbol;
    class Package;
    class Func;


    class Obj
    {
        public:

            enum eObjectType
            {
                eBaseObj  = 0,
                eNullObj,
                eStringObj,
                eConsObj,
                eFixnumObj,
                eFloatnumObj,
                eSymbolObj,
                ePackageObj,
                eFunctionObj
            };

            /* api any lispobj must implement */
            virtual eObjectType getObjectType() const = 0;

            /* create a fresh one */
            virtual Obj* create(void) const = 0;

            /* make a copy */
            virtual Obj* clone(void) const = 0;

            /* print to stream */
            virtual void print(std::ostream& out) const = 0;

            /* check a string to see if it represents this kind of object */
            //virtual bool identify(std::string in) const = 0;

            /* compare by value */
            virtual bool operator==(const Obj* other) = 0;
            
            inline bool hasRef() {
                return (references_ != 0);
            }

            inline void incRef() {
                references_++;
            }

            inline void decRef() {
                assert(references_ != 0);
                references_--;
            }


        protected:
            Obj() {};
            Obj(const Obj& other) {};
            Obj& operator=(const Obj& other) {};

            std::size_t references_;

    }; /* class Obj */

	typedef long FixnumValue;
	typedef double FloatnumValue;
	typedef std::string StringValue;
	
    class Env;

/** The lisp environment: an associative container that associates symbols
    with their properties **/

    class Env {

        private:

            /** parent namespace **/
            Env *parent_;

            // to do -- this needs to be a hash table or something
            // with faster lookup.
            typedef std::pair<Obj*,Obj*> Binding;

            std::vector<Binding> env_;

            /**
             * detect if a symbol is bound
             */
            class IsBound
            {
                private:
                    Obj* bound_;
                public:
                    IsBound(Obj* bound) :
                        bound_(bound)
                    {}

                    bool operator()(const Env::Binding& binding) {
                        return (bound_ == binding.first);
                    }
            }; /* class IsBound */

            class DecBindingRef
            {
                public:
                    DecBindingRef() {};
                    void operator()(const Env::Binding& binding) {
                        binding.first->decRef();
                        binding.second->decRef();
                        if (!binding.first->hasRef())
                            delete binding.first;
                        if (!binding.second->hasRef())
                            delete binding.second;
                    }
            };


            static Env *root_environment;
            static Env *current_environment;

        public:


            Env() :
                parent_(NULL)
            {
                root_environment = this;
                current_environment = this;
            };

            Env(Env* parent) :
                parent_(parent)
            {
            }

            std::size_t add(Obj* obj)
            {
                Binding bind(obj, NULL);
                obj->incRef();
                std::size_t result = env_.size();
                env_.push_back(bind);
                return result;
            }

            // test if object has been bound by value
            bool isBound(Obj* obj)
            {
                std::vector<Binding>::iterator result = std::find_if(env_.begin(), env_.end(), IsBound(obj));
                if ((result == env_.end()) && (parent_ != NULL))
                    return parent_->isBound(obj);
                else
                    return (result != env_.end());
            }


            //! return pointer to bound object that has same value
            Obj* bound(Obj* obj)
            {
                std::vector<Binding>::iterator result;
                result = std::find_if(env_.begin(), env_.end(), IsBound(obj));
                if (result == env_.end()) {
                    if (parent_ != NULL)
                    {
                        return parent_->bound(obj);
                    } else
                        return NULL;
                } else {
                    return result->first;
                }
            }

            // return pointer to bound value
            Obj* boundto(Obj* obj)
            {
                std::vector<Binding>::iterator result;
                result = std::find_if(env_.begin(), env_.end(), IsBound(obj));
                if (result == env_.end())
                    if (parent_ != NULL)
                        return parent_->boundto(obj);
                    else
                        return NULL;
                else
                    return result->second;
            }


            std::size_t bind(Obj *value, Obj* binding)
            {
                Obj *bindee = bound(value);
                if (bindee == NULL)
                    bindee = value;
                Binding bind(bindee, binding);
                bindee->incRef();
                binding->incRef();
                std::size_t result = env_.size();
                env_.push_back(bind);
                return result;
            }

            void unbind(Obj *value)
            {
                std::vector<Binding>::iterator binder;
                binder = std::find_if(env_.begin(), env_.end(), IsBound(value));
                if (binder == env_.end()) {
                    if (parent_ != NULL)
                        parent_->unbind(value);
                    else
                        return;
                }
                else {
                    DecBindingRef finalizer;
                    finalizer(*binder);
                    env_.erase(binder);
                }
                return;
            }

            Env *child(void)
            {
                current_environment = new Env(this);
                return current_environment;
            }

            virtual ~Env()
            {
                DecBindingRef finalizer;
                for_each(env_.begin(), env_.end(), finalizer);

                assert(this == Env::current_environment);
                Env::current_environment = parent_;
            }

    };

}


#endif


