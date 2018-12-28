
#define CONCAT_IMPL(a, b) a##b
#define CONCAT(a,b) CONCAT_IMPL(a,b)

#ifdef __COUNTER__
#define ANON(a) CONCAT(a, __COUNTER__)
#define ANON2(a) CONCAT_IMPL(a, __COUNTER__)
#else
#error "Nah"
#endif

#define _STR(x) #x
#define TO_STR(x) _STR(x)
#define Q_UNIQ(name) "" TO_STR(ANON(name)) ""
#define Q_UNIQ2(name) "" TO_STR(ANON2(name)) ""


namespace utl {

    template <typename Fun>
    class ScopeGuard {
    public:
        ScopeGuard(Fun &&f) : _fun(std::forward<Fun>(f)), _active(true) {
        }

        ~ScopeGuard() {
            if (_active) {
                _fun();
            }
        }

        void dismiss() {
            _active = false;
        }

        ScopeGuard() = delete;
        ScopeGuard(const ScopeGuard &) = delete;
        ScopeGuard &operator=(const ScopeGuard &) = delete;

        ScopeGuard(ScopeGuard &&rhs) : _fun(std::move(rhs._fun)), _active(rhs._active) {
            rhs.dismiss();
        }

    private:
        Fun _fun;
        bool _active;
    };

    enum class ScopeGuardOnExit {};
    template <typename Fun>
    ScopeGuard<Fun>
    operator+(ScopeGuardOnExit, Fun&& f) {
        return ScopeGuard<Fun>(std::forward<Fun>(f));
    }
}

#define SCOPE_EXIT \
    auto ANON(SCOPE_EXIT_STATE) \
    = ::utl::ScopeGuardOnExit() + [&]()
