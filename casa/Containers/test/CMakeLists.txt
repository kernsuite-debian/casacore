set (tests
tBlock
tBlockTrace
tObjectStack
tRecord
tRecordDesc
tValueHolder
)

if (BUILD_DEPRECATED)
   list (APPEND tests
       tHashMap
       tHashMapIO
       tHashMapIter
       tList
       tOrdMap2
       tOrdMap
       tQueue
       tSimOrdMap
       tStack
   )
endif ()

foreach (test ${tests})
    add_executable (${test} ${test}.cc)
    target_link_libraries (${test} casa_casa)
    add_test (${test} ${CMAKE_SOURCE_DIR}/cmake/cmake_assay ./${test})
    add_dependencies(check ${test})
endforeach (test)
