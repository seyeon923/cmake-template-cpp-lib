using mylib.CLR;

try
{
    Console.WriteLine($"mylib.CLR Version: {typeof(Useless).Assembly.GetName().Version}");

    using (var useless = new Useless())
    {
        if (Functions.IsExOptVarDefined())
        {
            Console.WriteLine("EX_OPT_VAR defined");
        }
        else
        {
            Console.WriteLine("EX_OPT_VAR not defined");
        }

        Console.WriteLine("\nCall Functions.CppFunction(\"Hello\", 2)");
        Console.WriteLine($"Return: {Functions.CppFunction("Hello", 2)}");
    }
}
catch (Exception)
{
    return -1;
}

return 0;