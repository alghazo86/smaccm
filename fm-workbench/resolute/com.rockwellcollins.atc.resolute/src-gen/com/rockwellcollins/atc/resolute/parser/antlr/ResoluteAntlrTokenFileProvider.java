/*
 * generated by Xtext
 */
package com.rockwellcollins.atc.resolute.parser.antlr;

import java.io.InputStream;
import org.eclipse.xtext.parser.antlr.IAntlrTokenFileProvider;

public class ResoluteAntlrTokenFileProvider implements IAntlrTokenFileProvider {
	
	@Override
	public InputStream getAntlrTokenFile() {
		ClassLoader classLoader = getClass().getClassLoader();
    	return classLoader.getResourceAsStream("com/rockwellcollins/atc/resolute/parser/antlr/internal/InternalResolute.tokens");
	}
}
