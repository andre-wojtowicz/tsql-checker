select *
From   TableName
WHERE  someField > ALL (SELECT [val] FROM [AnotherTable]);
