package ai.serenade.treesitter.query.internals;

import java.lang.ref.Cleaner;

public abstract class ResourceWithPointer implements AutoCloseable{
    protected long pointer;
    protected boolean isDeleted;
    private static final Cleaner cleaner = Cleaner.create();

    // Class used to clean the resources
    static class State implements Runnable {
        ResourceWithPointer resource;

        State(ResourceWithPointer resource) {
            this.resource = resource;
        }
        public void run() {
            this.resource.delete();
        }
    }

    public ResourceWithPointer() {
        this.pointer = 0;
        this.isDeleted = false;
        cleaner.register(this, new State(this));
    }

    private void delete() {
        if(!isDeleted && this.pointer > 0) {
            this.deleteObject();
        }
        isDeleted = true;
        this.pointer = 0;
    }

    @Override
    public void close() {
        delete();
    }

    abstract protected void deleteObject();
}
