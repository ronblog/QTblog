/****************************************************************************
  **
  ** Copyright (C) 2016 The Qt Company Ltd.
  ** Contact: https://www.qt.io/licensing/
  **
  ** This file is part of the examples of the Qt Toolkit.
  **
  ** $QT_BEGIN_LICENSE:BSD$
  ** Commercial License Usage
  ** Licensees holding valid commercial Qt licenses may use this file in
  ** accordance with the commercial license agreement provided with the
  ** Software or, alternatively, in accordance with the terms contained in
  ** a written agreement between you and The Qt Company. For licensing terms
  ** and conditions see https://www.qt.io/terms-conditions. For further
  ** information use the contact form at https://www.qt.io/contact-us.
  **
  ** BSD License Usage
  ** Alternatively, you may use this file under the terms of the BSD license
  ** as follows:
  **
  ** "Redistribution and use in source and binary forms, with or without
  ** modification, are permitted provided that the following conditions are
  ** met:
  **   * Redistributions of source code must retain the above copyright
  **     notice, this list of conditions and the following disclaimer.
  **   * Redistributions in binary form must reproduce the above copyright
  **     notice, this list of conditions and the following disclaimer in
  **     the documentation and/or other materials provided with the
  **     distribution.
  **   * Neither the name of The Qt Company Ltd nor the names of its
  **     contributors may be used to endorse or promote products derived
  **     from this software without specific prior written permission.
  **
  **
  ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  ** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  ** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  ** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  ** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  ** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  ** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  ** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  ** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  ** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  ** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
  **
  ** $QT_END_LICENSE$
  **
  ****************************************************************************/

  #include "imagecomposer.h"

  #include <QtWidgets>

  static const QSize resultSize(200, 200);

  ImageComposer::ImageComposer(QWidget* p)
	  :QWidget(p )
  {
	  sourceButton = new QToolButton;
	  sourceButton->setIconSize(resultSize);

	  operatorComboBox = new QComboBox;
	  addOp(QPainter::CompositionMode_SourceOver, tr("SourceOver"));
	  addOp(QPainter::CompositionMode_DestinationOver, tr("DestinationOver"));
	  addOp(QPainter::CompositionMode_Clear, tr("Clear"));
	  addOp(QPainter::CompositionMode_Source, tr("Source"));
	  addOp(QPainter::CompositionMode_Destination, tr("Destination"));
	  addOp(QPainter::CompositionMode_SourceIn, tr("SourceIn"));
	  addOp(QPainter::CompositionMode_DestinationIn, tr("DestinationIn"));
	  addOp(QPainter::CompositionMode_SourceOut, tr("SourceOut"));
	  addOp(QPainter::CompositionMode_DestinationOut, tr("DestinationOut"));
	  addOp(QPainter::CompositionMode_SourceAtop, tr("SourceAtop"));
	  addOp(QPainter::CompositionMode_DestinationAtop, tr("DestinationAtop"));
	  addOp(QPainter::CompositionMode_Xor, tr("Xor"));
	  addOp(QPainter::CompositionMode_Plus, tr("Plus"));
	  addOp(QPainter::CompositionMode_Multiply, tr("Multiply"));
	  addOp(QPainter::CompositionMode_Screen, tr("Screen"));
	  addOp(QPainter::CompositionMode_Overlay, tr("Overlay"));
	  addOp(QPainter::CompositionMode_Darken, tr("Darken"));
	  addOp(QPainter::CompositionMode_Lighten, tr("Lighten"));
	  addOp(QPainter::CompositionMode_ColorDodge, tr("ColorDodge"));
	  addOp(QPainter::CompositionMode_ColorBurn, tr("ColorBurn"));
	  addOp(QPainter::CompositionMode_HardLight, tr("HardLight"));
	  addOp(QPainter::CompositionMode_SoftLight, tr("SoftLight"));
	  addOp(QPainter::CompositionMode_Difference, tr("Difference"));
	  addOp(QPainter::CompositionMode_Exclusion, tr("Exclusion"));

	  destinationButton = new QToolButton;
	  destinationButton->setIconSize(resultSize);

	  QSpacerItem* sp = new QSpacerItem(2, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);



	  resultLabel = new QLabel;
	  resultLabel->setMinimumWidth(resultSize.width());
	   QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	  resultLabel->setSizePolicy( sizePolicy);
	  resultLabel->setFrameShape( QFrame:: Box);

	  connect(sourceButton, SIGNAL(clicked()), this, SLOT(chooseSource()));
	  connect(operatorComboBox, SIGNAL(activated(int)), this, SLOT(recalculateResult()));
	  connect(destinationButton, SIGNAL(clicked()), this, SLOT(chooseDestination()));

	  QGridLayout *mainLayout = new QGridLayout;
	  mainLayout->addWidget(sourceButton, 0, 0);
	  mainLayout->addWidget(destinationButton, 0, 1);

	  mainLayout->addWidget(operatorComboBox, 1, 0);
	  mainLayout->addItem(sp, 2, 0);

	  mainLayout->addWidget(resultLabel, 0, 2,3,2);
	 // mainLayout->setSizeConstraint(QLayout::SetMaximumSize);
	  setLayout(mainLayout);

	  resultImage = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);

	  loadImage(":/images/butterfly.png", &sourceImage, sourceButton);
	  loadImage(":/images/checker.png", &destinationImage, destinationButton);

	  setWindowTitle(tr("Image Composition"));
  }

  void ImageComposer::chooseSource()
  {
	  chooseImage(tr("Choose Source Image"), &sourceImage, sourceButton);
  }

  void ImageComposer::chooseDestination()
  {
	  chooseImage(tr("Choose Destination Image"), &destinationImage, destinationButton);
  }

  void ImageComposer::recalculateResult()
  {
	  QPainter::CompositionMode mode = currentMode();

	  QPainter painter(&resultImage);
	  painter.setCompositionMode(QPainter::CompositionMode_Source);
	  painter.fillRect(resultImage.rect(), Qt::transparent);
	  painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
	  painter.drawImage(0, 0, destinationImage);
	  painter.setCompositionMode(mode);
	  painter.drawImage(0, 0, sourceImage);
	  painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
	  painter.fillRect(resultImage.rect(), Qt::white);
	  painter.end();

	  resultLabel->setPixmap(QPixmap::fromImage(resultImage));
  }

  void ImageComposer::addOp(QPainter::CompositionMode mode, const QString &name)
  {
	  operatorComboBox->addItem(name, mode);
  }

  void ImageComposer::chooseImage(const QString &title, QImage *image,
								  QToolButton *button)
  {
	  QString fileName = QFileDialog::getOpenFileName(this, title);
	  if (!fileName.isEmpty())
		  loadImage(fileName, image, button);
  }

  void ImageComposer::loadImage(const QString &fileName, QImage *image,
								QToolButton *button)
  {
	  image->load(fileName);

	  // Scale the image to given size
	  *image = image->scaled(resultSize, Qt::KeepAspectRatio);

	  QImage fixedImage(resultSize, QImage::Format_ARGB32_Premultiplied);
	  QPainter painter(&fixedImage);
	  painter.setCompositionMode(QPainter::CompositionMode_Source);
	  painter.fillRect(fixedImage.rect(), Qt::transparent);
	  painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
	  painter.drawImage(imagePos(*image), *image);
	  painter.end();
	  button->setIcon(QPixmap::fromImage(fixedImage));

	  *image = fixedImage;

	  recalculateResult();
  }

  QPainter::CompositionMode ImageComposer::currentMode() const
  {
	  return (QPainter::CompositionMode)
			 operatorComboBox->itemData(operatorComboBox->currentIndex()).toInt();
  }

  QPoint ImageComposer::imagePos(const QImage &image) const
  {
	  return QPoint((resultSize.width() - image.width()) / 2,
					(resultSize.height() - image.height()) / 2);
  }
