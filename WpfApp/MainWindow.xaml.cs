using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using ViewModel;

namespace WpfApp
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window
	{
		private const string BinExt = ".bin";

		public MainWindow()
		{
			InitializeComponent();
		}


		private void OpenCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
		{
			e.CanExecute = true;
		}

		private void OpenCommand_Executed(object sender, ExecutedRoutedEventArgs e)
		{
			try
			{
				OpenFileDialog dialog = new OpenFileDialog
				{
					Filter = Properties.Resources.BinFilter,
					DefaultExt = BinExt
				};
				if ( !dialog.ShowDialog().GetValueOrDefault() )
					return;

				TreeNodeVM vm = TreeNodeVM.Open( dialog.FileName );
				vm.ExpandAll();
				SetRootNode( vm );
			}
			catch ( Exception ex )
			{
				MessageBox.Show( ex.Message, Properties.Resources.Error, MessageBoxButton.OK, MessageBoxImage.Error );
			}
		}

		private void SaveCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
		{
			e.CanExecute = RootNode != null;
		}

		private void SaveCommand_Executed(object sender, ExecutedRoutedEventArgs e)
		{
			try
			{
				SaveFileDialog dialog = new SaveFileDialog
				{
					Filter = Properties.Resources.BinFilter,
					DefaultExt = BinExt
				};
				if ( dialog.ShowDialog().GetValueOrDefault() )
					RootNode.Save( dialog.FileName );
			}
			catch ( Exception ex )
			{
				MessageBox.Show( ex.Message, Properties.Resources.Error, MessageBoxButton.OK, MessageBoxImage.Error );
			}
		}

		private void NewCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
		{
			TreeNodeVM vm = e.Parameter as TreeNodeVM;
			e.CanExecute = vm != null || RootNode == null;
		}

		private void NewCommand_Executed(object sender, ExecutedRoutedEventArgs e)
		{
			TreeNodeVM vmParent = e.Parameter as TreeNodeVM;
			TreeNodeVM vmNew = new TreeNodeVM();
			if ( vmParent != null )
			{
				vmParent.Children.Add( vmNew );
				UpdateTreeString();
			}
			else
				SetRootNode( vmNew );
		}

		private void DeleteCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e)
		{
			TreeNodeVM vm = e.Parameter as TreeNodeVM;
			e.CanExecute = vm != null;
		}

		private void DeleteCommand_Executed(object sender, ExecutedRoutedEventArgs e)
		{
			TreeNodeVM vm = e.Parameter as TreeNodeVM;
			if ( vm.Parent != null )
			{
				vm.Parent.Children.Remove( vm );
				UpdateTreeString();
			}
			else
				SetRootNode( null );
		}

		private void Tree_SelectedItemChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
		{
			SelectedNode = e.NewValue as TreeNodeVM;
		}

		private void NodeView_TextChanged(object sender, TextChangedEventArgs e)
		{
			UpdateTreeString();
		}


		private void SetRootNode(TreeNodeVM vm)
		{
			DataContext = new TreeNodeVM[] { vm };
			UpdateTreeString();
		}

		private void UpdateTreeString()
		{
			TreeString = RootNode?.ToSubtreeString();
		}


		public TreeNodeVM RootNode => ( DataContext as TreeNodeVM[] )?[0];

		public TreeNodeVM SelectedNode
		{
			get { return (TreeNodeVM) GetValue( SelectedNodeProperty ); }
			set { SetValue( SelectedNodeProperty, value ); }
		}

		public static readonly DependencyProperty SelectedNodeProperty =
			 DependencyProperty.Register( "SelectedNode", typeof( TreeNodeVM ), typeof( MainWindow ) );

		public string TreeString
		{
			get { return (string) GetValue( TreeStringProperty ); }
			set { SetValue( TreeStringProperty, value ); }
		}

		public static readonly DependencyProperty TreeStringProperty =
			 DependencyProperty.Register( "TreeString", typeof( string ), typeof( MainWindow ) );

	}
}
