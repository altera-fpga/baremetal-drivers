# Return values and error handling

This page explains how to read a result from the bare-metal APIs. It describes the conventions those APIs actually use. The cause of a particular code, and what to do next, is in the **Return values and error handling** section of the module guide.

## Two different questions

For a status-returning function, first check whether the operation succeeded, then interpret its outputs. For a data-returning function, the return value itself may be a handle, Boolean, count or register value. A `void` function reports no return status.

For APIs with a verified status contract, success means the operation described by that API completed. The [FCS guide](api/fcs/README.md) identifies unresolved output-validity exceptions in this release. The value it wrote can still describe a fault. A CCU uncorrected-error status of non-zero is a successful read of a register that reports a hardware error. A NoC Probe validity flag of false is a successful read that found no latched error in that logger, which is not a statement that the system is healthy.

## What a return value is

Functions that report status return `int` or `int32_t`.

- **Success is the value that function documents**, most often `0`. Do not assume every API returns zero. Some return a handle, a Boolean, a count, or nothing.
- **A negative errno-style value** is the negation of a name in this repository's `include/errno.h`. `-EINVAL` means "minus the `EINVAL` symbol". Compare with the symbol (`rc == -EINVAL`). Do not hard-code an integer from another C library; the numeric values in this tree are not a portability promise.
- **Some modules do not use errno.** ECC returns `ECC_API_*` and FCS returns `FCS_API_*`. Those names can be negative. Compare with the module's names. `ECC_API_EINVAL` is not `-EINVAL`.

Other return shapes:

| Shape | How to read it |
|---|---|
| `void` | The function reports no status. A problem may show up only as unchanged hardware or a later call's failure. |
| `bool` | The Boolean is the answer, not a status code. It is not errno. |
| Pointer or handle | The returned object is the success result. `NULL` is the failure result of that call, unless the module guide says otherwise. There is often no separate errno from an `open`. |
| Count | A positive value is data. Zero can mean "nothing happened" or "nothing is present" rather than a failed call. The module guide says which. |

## Codes that recur

The paragraphs below are the shared meaning. They do not replace the function-specific cause in the module guide.

### `-EINVAL`

The function rejected an argument **it checks**. Typical checks in this tree are a NULL pointer, a zero base address on a `*_with_base` call, a handle that is not open, or a value outside a range that function tests. Do not assume the function validates every address, index or buffer; only rely on the checks documented for that call. An address or index the function does not validate can hang or fault instead of returning `-EINVAL`, because the access never comes back to software.

On `-EINVAL`, use output parameters only when the module table explicitly
defines their contents. A failure can occur after an output was written: for
example, Clock Manager can write a zero frequency or divider and then reject
it, and CRC validation can initialize its result before rejecting the image.

### `-ENOSYS`

The no-base (platform-default) call cannot run because this build does not define that block's base, or the base it would use is zero. It means the **build** has no default address for that call. It does not, by itself, mean the silicon lacks the block.

Use the matching `*_with_base` function only when **that** function exists and you have a base address that your platform configuration approves. If the guide lists no `*_with_base` variant, this API has no alternative for that call.

On `-ENOSYS` from a default-base wrapper, the lower-level access is not performed.

### `-ETIMEDOUT`

A loop stopped because the completion condition was still false when the budget ran out. Check the module guide for the budget and how it is enforced:

- `timeout_polls`, or a fixed poll count such as `CCU_API_DEFAULT_TIMEOUT_POLLS`, counts **polls**, not milliseconds.
- Names such as `timeout_ms` and `timeout_us` indicate the intended unit, but do not guarantee a measured wall-clock deadline. For example, DMA implements `timeout_ms` as a scaled iteration budget.

A timeout does not mean the hardware rolled the operation back. Earlier steps in the same call may already have taken effect. Do not treat "try again with a larger budget" as a general recovery. The module guide states what was awaited and what state is unknown.

### Other errno-style names used by these APIs

| Symbol | Shared meaning in this tree | Still read the module table because |
|---|---|---|
| `-EBUSY` | The software context or the hardware is already in a state the call refuses | The busy condition is specific: already open, already initialized, or a controller still active |
| `-EIO` | The controller or a lower layer reported that the operation failed | The lower-layer cause is not one thing |
| `-ENODEV` | The requested device or usable device context is unavailable | It can mean a missing device, failed controller open, or absent initialized context; the function-specific cause matters |
| `-ERANGE` | A value is outside the range the call can represent | Which argument and which limit |
| `-EOVERFLOW` | The requested range would wrap past the end of the address space | Which address and length |
| `-ENOMEM` | An internal table or buffer had no free entry | Which table, and that retrying does not create space |
| `-EAGAIN` | The call could not finish now | Whether a later retry is meaningful |
| `-EOPNOTSUPP`, `-ENOTSUP` | That mode or feature is not implemented on this call | Which argument selects the unsupported mode |
| `-EPROTO` | The peer or the controller reported a protocol error | Which transfer |
| `-ENODATA` | The call looked and found nothing to return | "Nothing" can be a normal result, not a failure |
| `-EFAULT` | A pointer was rejected | Which pointer |
| `-EACCES` | Access was refused | Often a security or firewall decision, not a bad argument |

## When there is no software error to catch

If the interconnect firewall blocks the register, or the block's clock is off, or the block is held in reset, a load or store can hang the core or take a fault. These APIs cannot return a code for an access that never completes. Getting a return value at all means the function returned to its caller.

## Where to look next

Each module guide's **Return values and error handling** section names the function or the group of functions, the value, the condition that produces it, and what is safe to do with outputs and hardware state. Start with the guide for the module you are calling.
