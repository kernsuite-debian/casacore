set (tests
dCOWptr
dMUString
tBinarySearch
tBitVector
tCompare
tCompositeNumber
tCopy
tCountedPtr
tCOWPtr
tDataType
tDefaultValue
tDynBuffer
tFallible
tGenSort
tLinearSearch
tPrecision
tPtrHolder
tRegex_1
tRegex2
tRegex
tSort_1
tSort
tStringDistance
)

foreach (test ${tests})
    add_executable (${test} ${test}.cc)
    target_link_libraries (${test} casa_casa)
    add_test (${test} ${CMAKE_SOURCE_DIR}/cmake/cmake_assay ./${test})
    add_dependencies(check ${test})
endforeach (test)
