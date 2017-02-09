<Query Kind="Program">
  <Reference>&lt;RuntimeDirectory&gt;\System.Net.Http.dll</Reference>
  <NuGetReference>HtmlAgilityPack</NuGetReference>
  <Namespace>HtmlAgilityPack</Namespace>
  <Namespace>System.Globalization</Namespace>
  <Namespace>System.Net.Http</Namespace>
</Query>

void Main()
{
	string html;
	//using (var http = new HttpClient())
	//{
	//	http.DefaultRequestHeaders.Add("User-Agent", "LINQPad");
	//	//html = await http.GetStringAsync("https://support.microsoft.com/en-us/kb/318785");
	//	html = await http.GetStringAsync("https://support.microsoft.com/api/content/kb/318785");
	//	File.WriteAllText(Path.GetDirectoryName(Util.CurrentQueryPath) + "\\kb318785.html", html);
	//}
	
	html = File.ReadAllText(Path.GetDirectoryName(Util.CurrentQueryPath) + "\\kb318785.html");
	//html.Dump();
	HtmlDocument htmlDoc = new HtmlDocument();
	htmlDoc.LoadHtml(html);
	
	var nodeTable = htmlDoc.DocumentNode.SelectSingleNode("//table");
	Dictionary<string, List<RegInfo>> reg = new Dictionary<string, List<RegInfo>>();
	int rowNum = 0;
	string prevDotnetVer = "?????";
	foreach (var nodeTr in nodeTable.SelectNodes("tr"))
	{
		rowNum++;
		if (rowNum == 1) continue;
		
		string[] tds = nodeTr.SelectNodes("td").Select(node => {
			string txt = node.InnerText.Trim();
			//txt = Regex.Replace(txt, @"^\s+", "");
			//txt = Regex.Replace(txt, @"\s+$", "");
			//txt = Regex.Replace(txt, @"\s+", " ");
			return txt;
		}).ToArray();
		if (tds.Length != 4)
		{
			Console.WriteLine("WARNING: Skipping row at 'line {0}:column {1}' because <td> count isn't 4!", nodeTr.Line, nodeTr.LinePosition);
			continue;
		}
		
		string dotnetVer = tds[0];
		if (dotnetVer.Length == 0) dotnetVer = prevDotnetVer;
		
		string spLevel = tds[1];
		if (spLevel.Length>0 && spLevel != "Original Release") dotnetVer += " " + spLevel;
		
		RegInfo[] regInfos = RegInfo.Create(tds[2], tds[3]);
		if (!reg.ContainsKey(dotnetVer))
		{
			reg.Add(dotnetVer, new List<RegInfo>());
		}
		reg[dotnetVer].AddRange(regInfos);
		
		prevDotnetVer = dotnetVer;
	}
	
	reg.Dump();
	//reg.Keys.ToArray().Dump();
	//var keys = reg.Keys.ToArray();
	//Console.WriteLine (Char.GetUnicodeCategory(keys[7].Last()));
}

class RegInfo
{
	public string Key;
	public string OtherData;
	
	public static RegInfo[] Create(string keyInfo, string valueInfo)
	{
		return new[] {
			new RegInfo { Key = keyInfo, OtherData = valueInfo }
		};
	}
}

static class MyExt
{
	public static IEnumerable<T[]> StrictBatch<T>(this IEnumerable<T> source, int batchSize)
	{
		T[] arr = new T[batchSize];
		int count = 0;
		foreach (T item in source)
		{
			arr[count++] = item;
			if (count == batchSize)
			{
				yield return arr;
				count = 0;
				arr = new T[batchSize];
			}
		}
		if (count != 0) throw new InvalidOperationException("Invalid collection size");
	}
}
