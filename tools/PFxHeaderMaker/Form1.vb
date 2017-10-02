
Public Class Form1

	Dim workingfile As String = ""
	Dim workinglibpath As String = "../libraryincludes.h"

	Dim allegrodefines As List(Of String) = New List(Of String)()
	Dim sdl1defines As List(Of String) = New List(Of String)()
	Dim sdl2defines As List(Of String) = New List(Of String)()
	Dim pfxdefines As Dictionary(Of String, PFxDefine) = New Dictionary(Of String, PFxDefine)()
	Dim pfxtable As DataTable = New DataTable()

	Private cola As DataGridViewComboBoxColumn = New DataGridViewComboBoxColumn() With {.DataPropertyName = "Allegro Name", .Name = "Allegro Name"}
	Private cols1 As DataGridViewComboBoxColumn = New DataGridViewComboBoxColumn() With {.DataPropertyName = "SDL1 Name", .Name = "SDL1 Name"}
	Private cols2 As DataGridViewComboBoxColumn = New DataGridViewComboBoxColumn() With {.DataPropertyName = "SDL2 Name", .Name = "SDL2 Name"}


	Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
		DataGridView1.Columns.Add("PFx Name", "PFx Name")
		DataGridView1.Columns(0).DataPropertyName = "PFx Name"
		DataGridView1.Columns.Add(cola)
		DataGridView1.Columns.Add(cols1)
		DataGridView1.Columns.Add(cols2)

		For Each c As DataGridViewColumn In DataGridView1.Columns
			c.Width = 150
		Next
	End Sub


	Private Sub NewToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles NewToolStripMenuItem.Click
		Dim sfd As SaveFileDialog = New SaveFileDialog()
		sfd.Filter = "Header Files|*.h"
		If sfd.ShowDialog() = Windows.Forms.DialogResult.OK Then
			workingfile = sfd.FileName
			workinglibpath = "../libraryincludes.h"
			LoadData()
		End If
	End Sub

	Private Sub OpenToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles OpenToolStripMenuItem.Click
		Dim ofd As OpenFileDialog = New OpenFileDialog()
		ofd.Filter = "Header Files|*.h"
		If ofd.ShowDialog() = Windows.Forms.DialogResult.OK Then
			workingfile = ofd.FileName
			LoadData()
		End If
	End Sub

	Private Sub SaveToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SaveToolStripMenuItem.Click
		SaveData()
	End Sub

	Private Sub ExitToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ExitToolStripMenuItem.Click
		SaveData()
		Me.Close()
	End Sub

	Private Sub LoadData()
		Dim workingdir As String = IO.Path.GetDirectoryName(workingfile)
		If IO.File.Exists(IO.Path.Combine(workingdir, "allegro.h")) Then allegrodefines = GetDefines(IO.Path.Combine(workingdir, "allegro.h")) Else allegrodefines.Clear()
		If IO.File.Exists(IO.Path.Combine(workingdir, "sdl1.h")) Then sdl1defines = GetDefines(IO.Path.Combine(workingdir, "sdl1.h")) Else sdl1defines.Clear()
		If IO.File.Exists(IO.Path.Combine(workingdir, "sdl2.h")) Then sdl2defines = GetDefines(IO.Path.Combine(workingdir, "sdl2.h")) Else sdl2defines.Clear()

		cola.Items.Clear()
		cola.Items.AddRange(allegrodefines.ToArray())
		cols1.Items.Clear()
		cols1.Items.AddRange(sdl1defines.ToArray())
		cols2.Items.Clear()
		cols2.Items.AddRange(sdl2defines.ToArray())


		Dim currentmode As ProcessMode = ProcessMode.Unknown
		pfxdefines.Clear()

		If pfxtable.Columns.Count = 0 Then
			pfxtable.Columns.Add("PFx Name", GetType(String))
			pfxtable.Columns.Add("Allegro Name", GetType(String))
			pfxtable.Columns.Add("SDL1 Name", GetType(String))
			pfxtable.Columns.Add("SDL2 Name", GetType(String))
		End If
		pfxtable.Rows.Clear()

		If IO.File.Exists(workingfile) Then
			For Each line As String In IO.File.ReadAllLines(workingfile)

				If line.ToLower().Contains("libraryincludes.h") Then
					workinglibpath = line.Substring(line.IndexOf("""") + 1)
					workinglibpath = workinglibpath.Substring(0, workinglibpath.IndexOf(""""))
				End If

				If line.ToLower().Contains("allegro") Then currentmode = ProcessMode.Allegro
				If line.ToLower().Contains("sdl1") Then currentmode = ProcessMode.SDL1
				If line.ToLower().Contains("sdl2") Then currentmode = ProcessMode.SDL2

				If line.ToLower().StartsWith("#define") Then
					line = line.Substring(line.ToLower().IndexOf("#define") + 7).Trim().Replace(vbTab, " ")
					While line.Contains("  ")
						line.Replace("  ", " ")
					End While
					Dim kv() As String = Split(line, " ")

					If Not pfxdefines.ContainsKey(kv(0)) Then pfxdefines.Add(kv(0), New PFxDefine())
					If currentmode = ProcessMode.Allegro Then pfxdefines(kv(0)).AllegroName = kv(1)
					If currentmode = ProcessMode.SDL1 Then pfxdefines(kv(0)).SDL1Name = kv(1)
					If currentmode = ProcessMode.SDL2 Then pfxdefines(kv(0)).SDL2Name = kv(1)
				End If
			Next
		End If
		For Each k As String In pfxdefines.Keys
			pfxtable.Rows.Add(New Object() {k, pfxdefines(k).AllegroName, pfxdefines(k).SDL1Name, pfxdefines(k).SDL2Name})
		Next
		DataGridView1.DataSource = pfxtable
	End Sub

	Private Sub SaveData()
		Dim header As System.Text.StringBuilder = New System.Text.StringBuilder()

		header.AppendLine()
		header.AppendLine("#pragma once")
		header.AppendLine()
		header.AppendLine("#include """ & workinglibpath & """")
		header.AppendLine()
		header.AppendLine("#ifdef ALLEGRO")
		For Each row As DataRow In pfxtable.Rows
			If Not String.IsNullOrEmpty(Coalesce(row.Item("PFx Name"), "")) AndAlso Not String.IsNullOrEmpty(Coalesce(row.Item("Allegro Name"), "")) Then
				header.AppendLine("#define " & row.Item("PFx Name") & vbTab & row.Item("Allegro Name"))
			End If
		Next
		header.AppendLine("#endif // ALLEGRO")
		header.AppendLine()
		header.AppendLine("#ifdef SDL1")
		For Each row As DataRow In pfxtable.Rows
			If Not String.IsNullOrEmpty(Coalesce(row.Item("PFx Name"), "")) AndAlso Not String.IsNullOrEmpty(Coalesce(row.Item("SDL1 Name"), "")) Then
				header.AppendLine("#define " & row.Item("PFx Name") & vbTab & row.Item("SDL1 Name"))
			End If
		Next
		header.AppendLine("#endif // SDL1")
		header.AppendLine()
		header.AppendLine("#ifdef SDL2")
		For Each row As DataRow In pfxtable.Rows
			If Not String.IsNullOrEmpty(Coalesce(row.Item("PFx Name"), "")) AndAlso Not String.IsNullOrEmpty(Coalesce(row.Item("SDL2 Name"), "")) Then
				header.AppendLine("#define " & row.Item("PFx Name") & vbTab & row.Item("SDL2 Name"))
			End If
		Next
		header.AppendLine("#endif // SDL2")
		header.AppendLine()
		IO.File.WriteAllText(workingfile, header.ToString())
	End Sub

	Private Function GetDefines(Filename As String) As List(Of String)
		Dim defs As List(Of String) = New List(Of String)()
		Dim currentmode As ProcessMode = ProcessMode.Unknown

		For Each line As String In IO.File.ReadAllLines(Filename)
			line = line.Replace(vbTab, " ")

			If line.Contains("=") OrElse line.ToLower().Contains("#define") Then
				If line.Contains("=") Then line = line.Substring(0, line.IndexOf("=")).Trim()
				If line.ToLower().Contains("#define") Then line = line.Substring(line.ToLower().IndexOf("#define") + 7).Trim()
				If line.Contains(" ") Then line = line.Substring(0, line.IndexOf(" ")).Trim()

				defs.Add(line)

			End If

		Next
		Return defs
	End Function

	Public Function Coalesce(Value As Object, ParamArray NextValues() As Object)
		Dim v As Object = Value

		If v Is Nothing OrElse IsDBNull(v) Then
			Dim i As Integer = 0
			v = NextValues(i)
			While v Is Nothing OrElse IsDBNull(v) OrElse i = UBound(NextValues) - 1
				i += 1
				v = NextValues(i)
			End While
		End If
		Return v
	End Function

End Class
