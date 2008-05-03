
#ifndef H_LISP_OBJ
#define H_LISP_OBJ

#include <cassert>
#include <ostream>
#include <vector>


namespace Lisp
{
    typedef long FixNumValue;

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
                eFixNumObj,
                eFloatObj,
                eSymbolObj,
                ePackageObj,
                eFunctionObj
            };

            /* api any lispobj must implement */
            virtual eLispObjectType getObjectType() const = 0;

            /* create a fresh one */
            virtual LispObj* create(void) const = 0;

            /* make a copy */
            virtual LispObj* clone(void) const = 0;

            /* print to stream */
            virtual void print(std::ostream& out) const = 0;

            /* check a string to see if it represents this kind of object */
            //virtual bool identify(std::string in) const = 0;

            /* compare by value */
            virtual bool operator==(const LispObj* other) = 0;

            /* convert to fixnum */
            virtual operator const FixNumValue() const { return 0; };
            
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
            LispObj() {};
            LispObj(const LispObj& other) {};
            LispObj& operator=(const LispObj& other) {};

            std::size_t references_;

    }; /* class LispObj */

    class LispEnv;

/** The lisp environment: an associative container that associates symbols
    with their properties **/

    class LispEnv {

        private:

            /** parent namespace **/
            LispEnv *parent_;

            // to do -- this needs to be a hash table or something
            // with faster lookup.
            typedef std::pair<LispObj*,LispObj*> Binding;

            std::vector<Binding> env_;

            /**
             * detect if a symbol is bound
             */
            class IsBound
            {
                private:
                    LispObj* bound_;
                public:
                    IsBound(LispObj* bound) :
                        bound_(bound)
                    {}

                    bool operator()(const LispEnv::Binding& binding) {
                        return (bound_ == binding.first);
                    }
            }; /* class IsBound */

            class DecBindingRef
            {
                public:
                    DecBindingRef() {};
                    void operator()(const LispEnv::Binding& binding) {
                        binding.first->decRef();
                        binding.second->decRef();
                        if (!binding.first->hasRef())
                            delete binding.first;
                        if (!binding.second->hasRef())
                            delete binding.second;
                    }
            };


            static LispEnv *root_environment;
            static LispEnv *current_environment;

        public:


            LispEnv() :
                parent_(NULL)
            {
                root_environment = this;
                current_environment = this;
            };

            LispEnv(LispEnv* parent) :
                parent_(parent)
            {
            }

            std::size_t add(LispObj* obj)
            {
                Binding bind(obj, NULL);
                obj->incRef();
                std::size_t result = env_.size();
                env_.push_back(bind);
                return result;
            }

            // test if object has been bound by value
            bool isBound(LispObj* obj)
            {
                std::vector<Binding>::iterator result = std::find_if(env_.begin(), env_.end(), IsBound(obj));
                if ((result == env_.end()) && (parent_ != NULL))
                    return parent_->isBound(obj);
                else
                    return (result != env_.end());
            }


            //! return pointer to bound object that has same value
            LispObj* bound(LispObj* obj)
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
            LispObj* boundto(LispObj* obj)
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


            std::size_t bind(LispObj *value, LispObj* binding)
            {
                LispObj *bindee = bound(value);
                if (bindee == NULL)
                    bindee = value;
                Binding bind(bindee, binding);
                bindee->incRef();
                binding->incRef();
                std::size_t result = env_.size();
                env_.push_back(bind);
                return result;
            }

            void unbind(LispObj *value)
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

            LispEnv *child(void)
            {
                current_environment = new LispEnv(this);
                return current_environment;
            }

            virtual ~LispEnv()
            {
                DecBindingRef finalizer;
                for_each(env_.begin(), env_.end(), finalizer);

                assert(this == LispEnv::current_environment);
                LispEnv::current_environment = parent_;
            }

    };

}


#endif


