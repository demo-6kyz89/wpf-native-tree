using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Globalization;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using Props = WpfApp.Properties;

namespace WpfApp
{
	/// <summary>
	/// Interaction logic for App.xaml
	/// </summary>
	public partial class App : Application
	{
		protected override void OnStartup(StartupEventArgs e)
		{
			try
			{
				Thread.CurrentThread.CurrentUICulture = new CultureInfo( Props.Settings.Default.Language );
				Thread.CurrentThread.CurrentCulture = CultureInfo.CreateSpecificCulture( Props.Settings.Default.Language );
			}
			catch ( Exception ex )
			{
				MessageBox.Show( ex.Message, Props.Resources.Error, MessageBoxButton.OK, MessageBoxImage.Error );
			}

			base.OnStartup( e );
		}
	}
}
