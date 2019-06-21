[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
Invoke-WebRequest -Uri http://www.antlr.org/download/antlr-4.7.2-complete.jar -OutFile antlr-4.7.2-complete.jar
Invoke-WebRequest -Uri https://raw.githubusercontent.com/antlr/grammars-v4/master/tsql/TSqlLexer.g4 -OutFile TSqlLexer.g4
Invoke-WebRequest -Uri https://raw.githubusercontent.com/antlr/grammars-v4/master/tsql/TSqlParser.g4 -OutFile TSqlParser.g4

# apply grammar fix

$file_content = Get-Content TSqlParser.g4
$new_file_content = $file_content.Replace("| '(' table_source_item_joined ')'", "| '(' table_source ')'").Replace(": table_source_item join_part*", ": table_source_item join_part*`r`n    | '(' table_source_item_joined ')' join_part*")
Set-Content -Path TSqlParser.g4 -Value $new_file_content

# Java 1.6 or higher

java -jar antlr-4.7.2-complete.jar -Dlanguage=Cpp -DexportMacro=ANTLR4CPP_PUBLIC TSqlLexer.g4
java -jar antlr-4.7.2-complete.jar -no-listener -Dlanguage=Cpp -DexportMacro=ANTLR4CPP_PUBLIC TSqlParser.g4

# apply C++ header fix

$file_content = Get-Content TSqlLexer.h
$new_file_content = $file_content.Replace("#include `"antlr4-runtime.h`"", "#include `"antlr4-runtime.h`"`r`n#undef NULL")
Set-Content -Path TSqlLexer.h -Value $new_file_content

$file_content = Get-Content TSqlParser.h
$new_file_content = $file_content.Replace("#include `"antlr4-runtime.h`"", "#include `"antlr4-runtime.h`"`r`n#undef NULL")
Set-Content -Path TSqlParser.h -Value $new_file_content

# move and cleanup

Move-Item TSqlLexer.h,TSqlLexer.cpp,TSqlParser.h,TSqlParser.cpp src/ -Force

Remove-Item antlr-4.7.2-complete.jar,TSqlLexer.*,TSqlParser.*
