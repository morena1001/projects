using System;

namespace SiatteIME
{
    class Program
    {
        static string output = @"C:\Users\josue\Projects\SiatteIME\test.txt";
        static string wordFile = @"C:\Users\josue\Projects\SiatteIME\Words.txt";

        static string[]? words;

        static void Main()
        {
            words = File.ReadAllLines(wordFile); 

            //Console.WriteLine(words.Length);

            Console.Write("Write: ");

            string input = Console.ReadLine();
            //WordFinder(input);
            input.Trim();

            foreach (string word in words)
            {
                if (word.StartsWith(input))
                    Console.WriteLine(word);
            }
        }
    }
}
