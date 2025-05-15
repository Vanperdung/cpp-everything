#ifndef __NON_COPYABLE_H__
#define __NON_COPYABLE_H__

namespace cppevt
{

class NonCopyable
{
public:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
    
protected:
    NonCopyable() = default;
    ~NonCopyable() = default;
};

} // namespace cppevt

#endif