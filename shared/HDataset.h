#ifndef HDATASET_H
#define HDATASET_H

/*
 *  HDataset.h
 *  helloHdf
 *
 *  Created by jian zhang on 6/13/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "HObject.h"
class HDataset : public HObject {
public:
	HDataset(const std::string & path);
	virtual ~HDataset() {}
	
	virtual char validate();

	virtual char raw_create(hid_t parentId);

	virtual char open(hid_t parentId = FileIO.fFileId);
	virtual void close();
	virtual int objectType() const;
	
	virtual hid_t dataType();
	virtual void createDataSpace();
	virtual char verifyDataSpace();
	virtual char dimensionMatched();
	
	virtual char write();
	virtual char read();
	virtual char write(float *data);
	virtual char read(float *data);
	
	int dataSpaceNumDimensions() const;
	void dataSpaceDimensions(int dim[3]) const;
	
	void resize();
	
	hid_t fDataSpace;
	hsize_t fDimension[3];
private:
	hid_t m_createProps;
	hsize_t	m_chunkSize[3];
};
#endif        //  #ifndef HDATASET_H
