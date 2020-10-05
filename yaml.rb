

maps = {
  "Global" =>[
    ["std::string", "name", :required],
    ["bool","constant",],
    ["std::string","type",],
    ["std::string","ir"]
  ] ,           
  "Arg" =>
  [
    %W(std::string type),
    %W(std::string value),
  ],
  "Instruction" =>
  [
    %W(std::string ir),
    %W(std::string opcode),
    %W(std::string reg),
    %W(std::vector<ir2yaml::Arg> args),
    %W(unsigned align)
  ],
  "Block" =>
  [
    %W(std::string name),
    %W(std::vector<ir2yaml::Instruction> ins),
  ],
  "Function" =>
  [
    %W(std::string name),
    %W(std::vector<ir2yaml::Arg> args),
    %W(std::string retType),
    %W(std::vector<ir2yaml::Block> blocks),
    %W(std::vector<std::string> attrs)
  ],

  "Module" =>
  [
    %W(std::vector<ir2yaml::Global> globals),
    %W(std::vector<ir2yaml::Function> functions),
  ]
}.each do |key, attrs|
  
  File.open(key.downcase + ".h", "w") do |h|
    File.open(key.downcase + ".cpp", "w") do |c|
      h.puts("#ifndef __" + key.upcase + "_H_")
      h.puts("#define __" + key.upcase + "_H_")

      h.puts ("namespace ir2yaml {");      
      h.puts ("struct #{key} {");

      h.print("  #{key}(")
      h.print(attrs.map {|(type,name)| "#{type} #{name}"} * ", ")
      
      h.print("):")
      h.print(attrs.map {|(type,name)| "#{name}(#{name})"} * ", ")
      h.puts("{}")
      
      h.puts("  #{key}(){}")
      attrs.each do |(type,name)|
        h.puts ("  #{type} #{name};")
      end
      
      
      h.puts ("};");
      h.puts ("}");
      

      h.puts "template <> struct llvm::yaml::MappingTraits<ir2yaml::#{key}> {"
      h.puts "static void mapping(IO &IO, ir2yaml::#{key} & #{key.downcase}){"

      attrs.each do |(type,name)|
        h.puts "  IO.mapRequired(\"#{name}\", #{key.downcase}.#{name});"
      end
      
      h.puts("};")
      h.puts ("};")

      
      h.puts("LLVM_YAML_IS_SEQUENCE_VECTOR(ir2yaml::#{key})")
      h.puts("#endif //__" + key.upcase + "_H_")
    end


    
  end


      
    
  
  puts key
end



          
               
        
               
               
