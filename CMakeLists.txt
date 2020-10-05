set(LLVM_LINK_COMPONENTS
  BitReader
  IRReader
  Core
  Support
  )

add_llvm_tool(ir2yaml
  ir2yaml.cpp
  global.cpp
  arg.cpp
  instruction.cpp
  block.cpp
  function.cpp
  module.cpp
  utils.cpp
  tostring.cpp
  DEPENDS
  )


