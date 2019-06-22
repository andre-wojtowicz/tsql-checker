select * -- inline comment
From   TableName /* multiline
                      comment */
WHERE  someField > ALL (SELECT [val] FROM [AnotherTable]);
