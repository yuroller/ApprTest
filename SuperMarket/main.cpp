#define APPROVALS_CATCH
#include "ApprovalTests.hpp"
#include <memory>

using namespace ApprovalTests;
auto defaultReporterDisposer =
Approvals::useAsDefaultReporter(std::make_shared<Windows::WinMergeReporter>());