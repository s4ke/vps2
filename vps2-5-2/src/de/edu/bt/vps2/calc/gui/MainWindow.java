package de.edu.bt.vps2.calc.gui;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;

import de.edu.bt.vps2.calc.logik.CalcLogic;

public class MainWindow extends JFrame {

	private CalcLogic calcLogik;

	private static final long serialVersionUID = 1L;
	private JPanel jContentPane = null;
	private JButton jBerechneButton = null;
	private JTextField jAnzeigeTextField = null;
	private JButton j1Button = null;
	private JButton jButton1 = null;
	private JButton j8Button = null;
	private JButton j6Button = null;
	private JButton j3Button = null;
	private JButton j2Button = null;
	private JButton j5Button = null;
	private JButton jButton7 = null;
	private JButton j4Button = null;
	private JButton j0Button = null;
	private JButton jAddButton = null;
	private JButton jSubButton = null;
	private JButton jMultButton = null;
	private JButton jDivButton = null;
	private JButton jCEButton = null;

	/**
	 * This method initializes jBerechneButton
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getJBerechneButton() {
		if (jBerechneButton == null) {
			jBerechneButton = new JButton();
			jBerechneButton.setText("Berechne");
			jBerechneButton.addMouseListener(new java.awt.event.MouseAdapter() {
				public void mouseClicked(java.awt.event.MouseEvent e) {
					System.out.println("mouseClicked() on Berechne");
					try {
						jAnzeigeTextField.setText(calcLogik.berechneErgebnis());
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				}
			});
		}
		return jBerechneButton;
	}

	/**
	 * This method initializes jAnzeigeTextField
	 * 
	 * @return javax.swing.JTextField
	 */
	private JTextField getJAnzeigeTextField() {
		if (jAnzeigeTextField == null) {
			jAnzeigeTextField = new JTextField();
			jAnzeigeTextField.setText("0");
			jAnzeigeTextField.setEnabled(false);
		}
		return jAnzeigeTextField;
	}

	/**
	 * This method initializes j1Button
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getJ1Button() {
		if (j1Button == null) {
			j1Button = new JButton();
			j1Button.setText("1");
			j1Button.addMouseListener(new java.awt.event.MouseAdapter() {
				public void mouseClicked(java.awt.event.MouseEvent e) {
					System.out.println("mouseClicked() on 1");
					try {
						calcLogik.zifferHinzu("1");
					} catch(RemoteException e2) {
						// TODO Auto-generated catch block
						e2.printStackTrace();
					}
					try {
						jAnzeigeTextField.setText(calcLogik.getAktuellerWert());
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				}
			});
		}
		return j1Button;
	}

	/**
	 * This method initializes jButton1
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getJButton1() {
		if (jButton1 == null) {
			jButton1 = new JButton();
			jButton1.setText("7");
			jButton1.addMouseListener(new java.awt.event.MouseAdapter() {
				public void mouseClicked(java.awt.event.MouseEvent e) {
					System.out.println("mouseClicked() on 7");
					try {
						calcLogik.zifferHinzu("7");
					} catch(RemoteException e2) {
						// TODO Auto-generated catch block
						e2.printStackTrace();
					}
					try {
						jAnzeigeTextField.setText(calcLogik.getAktuellerWert());
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				}
			});
		}
		return jButton1;
	}

	/**
	 * This method initializes j8Button
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getJ8Button() {
		if (j8Button == null) {
			j8Button = new JButton();
			j8Button.setText("8");
			j8Button.addMouseListener(new java.awt.event.MouseAdapter() {
				public void mouseClicked(java.awt.event.MouseEvent e) {
					System.out.println("mouseClicked() on 8");
					try {
						calcLogik.zifferHinzu("8");
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					try {
						jAnzeigeTextField.setText(calcLogik.getAktuellerWert());
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				}
			});
		}
		return j8Button;
	}

	/**
	 * This method initializes j6Button
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getJ6Button() {
		if (j6Button == null) {
			j6Button = new JButton();
			j6Button.setText("6");
			j6Button.addMouseListener(new java.awt.event.MouseAdapter() {
				public void mouseClicked(java.awt.event.MouseEvent e) {
					System.out.println("mouseClicked() on 6");
					try {
						calcLogik.zifferHinzu("6");
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					try {
						jAnzeigeTextField.setText(calcLogik.getAktuellerWert());
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				}
			});
		}
		return j6Button;
	}

	/**
	 * This method initializes j3Button
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getJ3Button() {
		if (j3Button == null) {
			j3Button = new JButton();
			j3Button.setText("3");
			j3Button.addMouseListener(new java.awt.event.MouseAdapter() {
				public void mouseClicked(java.awt.event.MouseEvent e) {
					System.out.println("mouseClicked() on 3");
					try {
						calcLogik.zifferHinzu("3");
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					try {
						jAnzeigeTextField.setText(calcLogik.getAktuellerWert());
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				}
			});
		}
		return j3Button;
	}

	/**
	 * This method initializes j2Button
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getJ2Button() {
		if (j2Button == null) {
			j2Button = new JButton();
			j2Button.setText("2");
			j2Button.addMouseListener(new java.awt.event.MouseAdapter() {
				public void mouseClicked(java.awt.event.MouseEvent e) {
					System.out.println("mouseClicked() on 2");
					try {
						calcLogik.zifferHinzu("2");
					} catch(RemoteException e2) {
						// TODO Auto-generated catch block
						e2.printStackTrace();
					}
					try {
						jAnzeigeTextField.setText(calcLogik.getAktuellerWert());
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				}
			});
		}
		return j2Button;
	}

	/**
	 * This method initializes j5Button
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getJ5Button() {
		if (j5Button == null) {
			j5Button = new JButton();
			j5Button.setText("5");
			j5Button.addMouseListener(new java.awt.event.MouseAdapter() {
				public void mouseClicked(java.awt.event.MouseEvent e) {
					System.out.println("mouseClicked() on 5");
					try {
						calcLogik.zifferHinzu("5");
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					try {
						jAnzeigeTextField.setText(calcLogik.getAktuellerWert());
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				}
			});
		}
		return j5Button;
	}

	/**
	 * This method initializes jButton7
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getJButton7() {
		if (jButton7 == null) {
			jButton7 = new JButton();
			jButton7.setText("9");
			jButton7.addMouseListener(new java.awt.event.MouseAdapter() {
				public void mouseClicked(java.awt.event.MouseEvent e) {
					System.out.println("mouseClicked() on 9");
					try {
						calcLogik.zifferHinzu("9");
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					try {
						jAnzeigeTextField.setText(calcLogik.getAktuellerWert());
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				}
			});
		}
		return jButton7;
	}

	/**
	 * This method initializes j4Button
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getJ4Button() {
		if (j4Button == null) {
			j4Button = new JButton();
			j4Button.setText("4");
			j4Button.addMouseListener(new java.awt.event.MouseAdapter() {
				public void mouseClicked(java.awt.event.MouseEvent e) {
					System.out.println("mouseClicked() on 4");
					try {
						calcLogik.zifferHinzu("4");
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					try {
						jAnzeigeTextField.setText(calcLogik.getAktuellerWert());
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				}
			});
		}
		return j4Button;
	}

	/**
	 * This method initializes j0Button
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getJ0Button() {
		if (j0Button == null) {
			j0Button = new JButton();
			j0Button.setText("0");
			j0Button.addMouseListener(new java.awt.event.MouseAdapter() {
				public void mouseClicked(java.awt.event.MouseEvent e) {
					System.out.println("mouseClicked() on 0");
					try {
						calcLogik.zifferHinzu("0");
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					try {
						jAnzeigeTextField.setText(calcLogik.getAktuellerWert());
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}

				}
			});
		}
		return j0Button;
	}

	/**
	 * This method initializes jAddButton
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getJAddButton() {
		if (jAddButton == null) {
			jAddButton = new JButton();
			jAddButton.setText("+");
			jAddButton.addMouseListener(new java.awt.event.MouseAdapter() {
				public void mouseClicked(java.awt.event.MouseEvent e) {
					System.out.println("mouseClicked() on +");
					try {
						calcLogik.setzeOperation("+");
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					try {
						jAnzeigeTextField.setText(calcLogik.getAktuellerWert());
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				}
			});
		}
		return jAddButton;
	}

	/**
	 * This method initializes jSubButton
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getJSubButton() {
		if (jSubButton == null) {
			jSubButton = new JButton();
			jSubButton.setText("-");
			jSubButton.addMouseListener(new java.awt.event.MouseAdapter() {
				public void mouseClicked(java.awt.event.MouseEvent e) {
					System.out.println("mouseClicked() on -");
					try {
						calcLogik.setzeOperation("-");
					} catch(RemoteException e2) {
						// TODO Auto-generated catch block
						e2.printStackTrace();
					}
					try {
						jAnzeigeTextField.setText(calcLogik.getAktuellerWert());
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				}
			});
		}
		return jSubButton;
	}

	/**
	 * This method initializes jMultButton
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getJMultButton() {
		if (jMultButton == null) {
			jMultButton = new JButton();
			jMultButton.setText("x");
			jMultButton.addMouseListener(new java.awt.event.MouseAdapter() {
				public void mouseClicked(java.awt.event.MouseEvent e) {
					System.out.println("mouseClicked() on x");
					try {
						calcLogik.setzeOperation("x");
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					try {
						jAnzeigeTextField.setText(calcLogik.getAktuellerWert());
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				}
			});
		}
		return jMultButton;
	}

	/**
	 * This method initializes jDivButton
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getJDivButton() {
		if (jDivButton == null) {
			jDivButton = new JButton();
			jDivButton.setText(":");
			jDivButton.addMouseListener(new java.awt.event.MouseAdapter() {
				public void mouseClicked(java.awt.event.MouseEvent e) {
					System.out.println("mouseClicked() on :");
					try {
						calcLogik.setzeOperation(":");
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					try {
						jAnzeigeTextField.setText(calcLogik.getAktuellerWert());
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				}
			});
		}
		return jDivButton;
	}

	/**
	 * This method initializes jCEButton
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getJCEButton() {
		if (jCEButton == null) {
			jCEButton = new JButton();
			jCEButton.setText("CE");
			jCEButton.addMouseListener(new java.awt.event.MouseAdapter() {
				public void mouseClicked(java.awt.event.MouseEvent e) {
					System.out.println("mouseClicked() on CE");
					try {
						calcLogik = MainWindow.getLogicFromServer();
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					} catch(NotBoundException e3) {
						// TODO Auto-generated catch block
						e3.printStackTrace();
					}
					try {
						jAnzeigeTextField.setText(calcLogik.getAktuellerWert());
					} catch(RemoteException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				}
			});
		}
		return jCEButton;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				MainWindow thisClass;
				try {
					thisClass = new MainWindow();
					thisClass.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
					thisClass.setVisible(true);
				} catch(RemoteException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch(NotBoundException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * This is the default constructor
	 * @throws RemoteException 
	 * @throws NotBoundException 
	 */
	public MainWindow() throws RemoteException, NotBoundException {
		super();
		initialize();
		this.calcLogik = getLogicFromServer();
	}
	
	private static CalcLogic getLogicFromServer() throws RemoteException, NotBoundException {
		//Zuerst verbinden wir zur Registry des entfernten RMI-Servers
		Registry reg = LocateRegistry.getRegistry("127.0.0.1",
				Registry.REGISTRY_PORT);
		//Anfragen eines "Calculator"-Objekts beim RMI-Server
		CalcLogic calc = (CalcLogic) reg.lookup("Calculator");
		//Beweis für die Verwendung von Proxie ab Java 5
		System.out.println(calc.getClass());
		return calc;
	}

	/**
	 * This method initializes this
	 * 
	 * @return void
	 */
	private void initialize() {
		this.setSize(200, 200);
		this.setContentPane(getJContentPane());
		this.setTitle("VPS2 simple Calc");
	}

	/**
	 * This method initializes jContentPane
	 * 
	 * @return javax.swing.JPanel
	 */
	private JPanel getJContentPane() {
		if (jContentPane == null) {
			GridBagConstraints gridBagConstraints17 = new GridBagConstraints();
			gridBagConstraints17.gridx = 3;
			gridBagConstraints17.fill = GridBagConstraints.HORIZONTAL;
			gridBagConstraints17.gridy = 4;
			GridBagConstraints gridBagConstraints16 = new GridBagConstraints();
			gridBagConstraints16.gridx = 0;
			gridBagConstraints16.fill = GridBagConstraints.HORIZONTAL;
			gridBagConstraints16.gridy = 4;
			GridBagConstraints gridBagConstraints15 = new GridBagConstraints();
			gridBagConstraints15.gridx = 0;
			gridBagConstraints15.fill = GridBagConstraints.HORIZONTAL;
			gridBagConstraints15.gridy = 3;
			GridBagConstraints gridBagConstraints14 = new GridBagConstraints();
			gridBagConstraints14.gridx = 0;
			gridBagConstraints14.fill = GridBagConstraints.HORIZONTAL;
			gridBagConstraints14.gridy = 2;
			GridBagConstraints gridBagConstraints13 = new GridBagConstraints();
			gridBagConstraints13.gridx = 0;
			gridBagConstraints13.fill = GridBagConstraints.HORIZONTAL;
			gridBagConstraints13.gridy = 1;
			GridBagConstraints gridBagConstraints12 = new GridBagConstraints();
			gridBagConstraints12.gridx = 2;
			gridBagConstraints12.fill = GridBagConstraints.HORIZONTAL;
			gridBagConstraints12.gridy = 4;
			GridBagConstraints gridBagConstraints11 = new GridBagConstraints();
			gridBagConstraints11.gridx = 1;
			gridBagConstraints11.fill = GridBagConstraints.HORIZONTAL;
			gridBagConstraints11.gridy = 2;
			GridBagConstraints gridBagConstraints10 = new GridBagConstraints();
			gridBagConstraints10.gridx = 2;
			gridBagConstraints10.gridy = 5;
			GridBagConstraints gridBagConstraints9 = new GridBagConstraints();
			gridBagConstraints9.gridx = 3;
			gridBagConstraints9.fill = GridBagConstraints.HORIZONTAL;
			gridBagConstraints9.gridy = 3;
			GridBagConstraints gridBagConstraints8 = new GridBagConstraints();
			gridBagConstraints8.gridx = 2;
			gridBagConstraints8.fill = GridBagConstraints.HORIZONTAL;
			gridBagConstraints8.gridy = 2;
			GridBagConstraints gridBagConstraints7 = new GridBagConstraints();
			gridBagConstraints7.gridx = 2;
			gridBagConstraints7.fill = GridBagConstraints.HORIZONTAL;
			gridBagConstraints7.gridy = 1;
			GridBagConstraints gridBagConstraints6 = new GridBagConstraints();
			gridBagConstraints6.gridx = 3;
			gridBagConstraints6.fill = GridBagConstraints.HORIZONTAL;
			gridBagConstraints6.gridy = 1;
			GridBagConstraints gridBagConstraints5 = new GridBagConstraints();
			gridBagConstraints5.gridx = 3;
			gridBagConstraints5.fill = GridBagConstraints.HORIZONTAL;
			gridBagConstraints5.gridy = 2;
			GridBagConstraints gridBagConstraints4 = new GridBagConstraints();
			gridBagConstraints4.gridx = 2;
			gridBagConstraints4.fill = GridBagConstraints.HORIZONTAL;
			gridBagConstraints4.gridy = 3;
			GridBagConstraints gridBagConstraints3 = new GridBagConstraints();
			gridBagConstraints3.gridx = 1;
			gridBagConstraints3.fill = GridBagConstraints.HORIZONTAL;
			gridBagConstraints3.gridy = 3;
			GridBagConstraints gridBagConstraints2 = new GridBagConstraints();
			gridBagConstraints2.gridx = 1;
			gridBagConstraints2.fill = GridBagConstraints.HORIZONTAL;
			gridBagConstraints2.gridy = 1;
			GridBagConstraints gridBagConstraints1 = new GridBagConstraints();
			gridBagConstraints1.fill = GridBagConstraints.BOTH;
			gridBagConstraints1.gridy = 0;
			gridBagConstraints1.weightx = 1.0;
			gridBagConstraints1.gridwidth = 4;
			gridBagConstraints1.gridx = 0;
			GridBagConstraints gridBagConstraints = new GridBagConstraints();
			gridBagConstraints.gridx = 0;
			gridBagConstraints.gridwidth = 4;
			gridBagConstraints.fill = GridBagConstraints.HORIZONTAL;
			gridBagConstraints.gridy = 5;
			jContentPane = new JPanel();
			jContentPane.setLayout(new GridBagLayout());
			jContentPane.add(getJBerechneButton(), gridBagConstraints);
			jContentPane.add(getJAnzeigeTextField(), gridBagConstraints1);
			jContentPane.add(getJ1Button(), gridBagConstraints2);
			jContentPane.add(getJButton1(), gridBagConstraints3);
			jContentPane.add(getJ8Button(), gridBagConstraints4);
			jContentPane.add(getJ6Button(), gridBagConstraints5);
			jContentPane.add(getJ3Button(), gridBagConstraints6);
			jContentPane.add(getJ2Button(), gridBagConstraints7);
			jContentPane.add(getJ5Button(), gridBagConstraints8);
			jContentPane.add(getJButton7(), gridBagConstraints9);
			jContentPane.add(getJ4Button(), gridBagConstraints11);
			jContentPane.add(getJ0Button(), gridBagConstraints12);
			jContentPane.add(getJAddButton(), gridBagConstraints13);
			jContentPane.add(getJSubButton(), gridBagConstraints14);
			jContentPane.add(getJMultButton(), gridBagConstraints15);
			jContentPane.add(getJDivButton(), gridBagConstraints16);
			jContentPane.add(getJCEButton(), gridBagConstraints17);
		}
		return jContentPane;
	}

}
