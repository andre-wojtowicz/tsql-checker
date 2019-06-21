# T-SQL checker

This program, for a given Transact-SQL file, outputs tokens and elements of T-SQL grammar produced by [ANTLR](https://www.antlr.org/) (ANother Tool for Language Recognition).

## Binaries

Windows and Linux binaries can be downloaded from [releases](https://github.com/andre-wojtowicz/tsql-checker/releases).

## Usage

Input `select.sql`:

```sql
select *
From   TableName
WHERE  someField > ALL (SELECT [val] FROM [AnotherTable]);
```

Execution:

```
./tsql-checker.exe select.sql
```

Output `select.tokens`:

```plaintext
select * From TableName WHERE someField > ALL ( SELECT [val] FROM [AnotherTable] ) ; <EOF> 
```


Output `select.grammar`:

```plaintext
tsql_file batch sql_clauses sql_clause dml_clause select_statement query_expression query_specification 
select_list select_list_elem asterisk table_sources table_source table_source_item_joined table_source_item 
table_name_with_hint table_name id simple_id search_condition search_condition_and search_condition_not 
predicate expression full_column_name id simple_id comparison_operator subquery select_statement 
query_expression query_specification select_list select_list_elem column_elem id table_sources table_source
table_source_item_joined table_source_item table_name_with_hint table_name id 
```

## Notes

`TSqlLexer.*` and `TSqlParser.*` are generated by ANTLR. They can be updated to the newest version of [ANTLR4 grammar for T-SQL](https://github.com/antlr/grammars-v4/tree/master/tsql) by running PowerShell script `update-parser-lexer.ps1`.
