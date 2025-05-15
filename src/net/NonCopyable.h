#ifndef __NON_COPYABLE_H__
#define __NON_COPYABLE_H__

namespace cppevt
{

class NonCopyable
{
protected:
    NonCopyable() = default;
    ~NonCopyable() = default;

private:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator==(const NonCopyable&) = delete;
};

} // namespace cppevt

#endif