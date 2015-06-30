package univ.c3.II.oop.client;

import com.google.gwt.user.client.rpc.RemoteService;
import com.google.gwt.user.client.rpc.RemoteServiceRelativePath;

import java.io.Serializable;

/**
 * Created by: witalia
 * Project name: hw7
 * Date: 15.12.14
 * Time: 9:11
 * All rights reserved.
 */
@RemoteServiceRelativePath("MessageService")
public interface MessageService extends RemoteService {
    Serializable getMessage(Serializable message);
}
